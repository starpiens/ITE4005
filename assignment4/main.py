import argparse
from typing import List, Dict
from os import path

import numpy as np
import tensorflow as tf
from tensorflow.keras import models, layers, metrics, losses, optimizers, callbacks, activations
import tensorflow.keras.backend as K


def read_records(path: str) \
        -> Dict[str, np.ndarray]:
    '''
    Read records from file.
    :param path: Path of data file.
    :return: Dictionary containing {attribute_name: attribute}
    '''
    f = open(path, 'r')
    attr_names = ['user_id', 'item_id', 'rating', 'timestamp']
    records = dict(zip(attr_names, [np.ndarray(shape=(0, 1), dtype=int)] * 4))

    while True:
        line = f.readline()
        if not line: break
        line = line.split('\t')
        for idx, name in enumerate(attr_names):
            records[name] = np.append(records[name], [[int(line[idx])]], axis=0)

    f.close()
    return records


def parse_args():
    parser = argparse.ArgumentParser()
    parser.add_argument("train_path", help="path of training data file", type=str)
    parser.add_argument("test_path", help="path of test data file", type=str)
    return parser.parse_args()


def main(train: bool):
    args = parse_args()

    train_data = read_records(args.train_path)

    user_input = layers.Input(shape=(1,))
    user_x = layers.Embedding(train_data['user_id'].max() + 1, 20, input_length=1, name='user_embed')(user_input)
    item_input = layers.Input(shape=(1,))
    item_x = layers.Embedding(train_data['item_id'].max() + 1, 20, input_length=1, name='item_embed')(item_input)
    rating = layers.Dot(axes=-1)([user_x, item_x])
    rating = layers.Flatten()(rating)
    # rating = activations.sigmoid(rating)
    # rating = layers.Lambda(lambda x : x * 4 + 1)(rating)
    model = models.Model([user_input, item_input], rating)

    model.summary()
    model.compile(optimizer=optimizers.Adam(1e-3),
                  loss=losses.mean_squared_error,
                  metrics=[metrics.RootMeanSquaredError()])

    val_data = read_records(args.test_path)

    if train:
        model.fit([train_data['user_id'], train_data['item_id']], train_data['rating'],
                  validation_data=([val_data['user_id'], val_data['item_id']], val_data['rating']),
                  callbacks=callbacks.EarlyStopping(patience=3),
                  batch_size=32, epochs=100)
        model.save_weights('checkpoints/' + path.splitext(path.basename(args.train_path))[0])

    rating = layers.Lambda(lambda x : K.round(x))(rating)
    final_model = models.Model(model.input, rating)
    final_model.compile()
    final_model.load_weights('checkpoints/' + path.splitext(path.basename(args.test_path))[0])
    print(final_model.evaluate([val_data['user_id'], val_data['item_id']], val_data['rating']))


if __name__ == '__main__':
    main(True)
