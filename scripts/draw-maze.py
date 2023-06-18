import cv2
import numpy as np
import random
import struct
import argparse

width = 500
height = 500

BLACK = (0, 0, 0)
WHITE = (255, 255, 255)

drawing_color = WHITE
drawing_thickness = 20
drawing_active = False

drawing = np.zeros((height, width), dtype=np.uint8)

def on_mouse(event, x, y, flags, param):
    global drawing_active
    if event == cv2.EVENT_LBUTTONDOWN:
        drawing_active = True
    elif event == cv2.EVENT_LBUTTONUP:
        drawing_active = False
    elif event == cv2.EVENT_MOUSEMOVE:
        if drawing_active:
            cv2.circle(drawing, (x, y), drawing_thickness, drawing_color, -1)


def generate_maze(height, width):
    maze = [[0 for _ in range(width)] for _ in range(height)]
    
    cv2.namedWindow("Paint")
    cv2.setMouseCallback("Paint", on_mouse)
    while True:
        cv2.imshow("Paint", drawing)

        key = cv2.waitKey(1) & 0xFF

        if key == ord('q'):
            break

    small_drawing = cv2.resize(drawing, (width, height), interpolation=cv2.INTER_LINEAR)

    indices = np.where(small_drawing == 255)
    positions = list(zip(indices[1], indices[0]))
    for position in positions:
        x, y = position
        maze[y][x] = 1

    for i in range(height):
        for j in range(width):
            if random.random() < 0.4:
                maze[i][j] = 1

    cv2.destroyAllWindows()

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
    parser.add_argument('n_linhas', type=int, help="Numero de linhas.")
    parser.add_argument('n_colunas', type=int, help="Numero de colunas.")
    return parser.parse_args()


def main():
    args = parse_args()
    maze = generate_maze(args.n_linhas, args.n_colunas)

    # print(maze  )
    save_maze(maze, args.output_path)


if __name__ == "__main__":
    main()