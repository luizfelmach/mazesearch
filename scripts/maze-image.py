import cv2
import numpy as np
import random
import struct
import argparse


def generate_maze(height, width, input_path):
    maze = [[0 for _ in range(width)] for _ in range(height)]

    image = cv2.imread(input_path, cv2.IMREAD_GRAYSCALE)

    # Converter a imagem em uma matriz
    drawing = np.array(image)

    small_drawing = cv2.resize(drawing, (width, height), interpolation=cv2.INTER_LINEAR)

    indices = np.where(small_drawing == 0)
    positions = list(zip(indices[1], indices[0]))
    for position in positions:
        x, y = position
        maze[y][x] = 1

    # for i in range(height):
    #     for j in range(width):
    #         if random.random() < 0.4:
    #             maze[i][j] = 1

    return maze


def save_maze(maze, output_path):
    with open(output_path, "wb") as f:
        f.write(struct.pack('i', len(maze)))
        f.write(struct.pack('i', len(maze[0])))

        for i in range(len(maze)):
            for j in range(len(maze[0])):
                f.write(struct.pack('B', maze[i][j]))


def parse_args():
    parser = argparse.ArgumentParser(description="Draw a maze.")
    parser.add_argument('output_path', type=str,
                        help="Caminho do arquivo onde a maze sera salva.")
    parser.add_argument('input_path', type=str,
                        help="Caminho da imagem.")
    parser.add_argument('n_linhas', type=int, help="Numero de linhas.")
    parser.add_argument('n_colunas', type=int, help="Numero de colunas.")
    return parser.parse_args()


def main():
    args = parse_args()
    maze = generate_maze(args.n_linhas, args.n_colunas, args.input_path)

    # print(maze  )
    save_maze(maze, args.output_path)


if __name__ == "__main__":
    main()