import os
import json
from tqdm import tqdm
import argparse

# parser = argparse.ArgumentParser()
# parser.add_argument('--json_path', default="C:\\Users\\30235\\Desktop\\parking_final\\Annotations\\coco_info.json", type=str,
#                     help="input: coco format(json)")
# parser.add_argument('--save_path', default="C:\\Users\\30235\\Desktop\\parking_final\\labels", type=str,
#                     help="specify where to save the output dir of labels")
# arg = parser.parse_args()
#
#
# def convert(size, box):
#     dw = 1. / (size[0])
#     dh = 1. / (size[1])
#     x = box[0] + box[2] / 2.0
#     y = box[1] + box[3] / 2.0
#     w = box[2]
#     h = box[3]
#
#     x = x * dw
#     w = w * dw
#     y = y * dh
#     h = h * dh
#     return (x, y, w, h)
#
#
# if __name__ == '__main__':
#     json_file = arg.json_path  # COCO Object Instance 类型的标注
#     ana_txt_save_path = arg.save_path  # 保存的路径
#
#     data = json.load(open(json_file, 'r'))
#     if not os.path.exists(ana_txt_save_path):
#         os.makedirs(ana_txt_save_path)
#
#     id_map = {}  # coco数据集的id不连续！重新映射一下再输出！
#     for i, category in enumerate(data['categories']):
#         id_map[category['id']] = i
#
#     # 通过事先建表来降低时间复杂度
#     max_id = 0
#     for img in data['images']:
#         max_id = max(max_id, img['id'])
#     # 注意这里不能写作 [[]]*(max_id+1)，否则列表内的空列表共享地址
#     img_ann_dict = [[] for i in range(max_id + 1)]
#     for i, ann in enumerate(data['annotations']):
#         img_ann_dict[ann['image_id']].append(i)
#
#     for img in tqdm(data['images']):
#         filename = img["file_name"]
#         img_width = img["width"]
#         img_height = img["height"]
#         img_id = img["id"]
#         head, tail = os.path.splitext(filename)
#         ana_txt_name = head + ".txt"  # 对应的txt名字，与jpg一致
#         f_txt = open(os.path.join(ana_txt_save_path, ana_txt_name), 'w')
#         '''for ann in data['annotations']:
#             if ann['image_id'] == img_id:
#                 box = convert((img_width, img_height), ann["bbox"])
#                 f_txt.write("%s %s %s %s %s\n" % (id_map[ann["category_id"]], box[0], box[1], box[2], box[3]))'''
#         # 这里可以直接查表而无需重复遍历
#         for ann_id in img_ann_dict[img_id]:
#             ann = data['annotations'][ann_id]
#             box = convert((img_width, img_height), ann["bbox"])
#             f_txt.write("%s %s %s %s %s\n" % (id_map[ann["category_id"]], box[0], box[1], box[2], box[3]))
#         f_txt.close()


# # import os
# #
# unlabeled_images_dir = "C:\\Users\\30235\\Desktop\\parking_final\\images"
# labels_dir = "C:\\Users\\30235\\Desktop\\parking_final\\labels"
#
# for image_file in os.listdir(unlabeled_images_dir):
#     image_path = os.path.join(unlabeled_images_dir, image_file)
#     label_path = os.path.join(labels_dir, os.path.splitext(image_file)[0] + '.txt')
#
#     if not os.path.exists(label_path):
#         os.remove(image_path)

import os

# folder_path = 'C:\\Users\\30235\\Desktop\\yolov5-master\\datasets\\coco128\\labels\\train2017'  # 标签文件夹路径
# import os

labels_folder = 'C:\\Users\\30235\\Desktop\\yolov5-master\\datasets\\coco128\\labels\\train2017'  # 标签文件夹路径
data_folder = 'C:\\Users\\30235\\Desktop\\yolov5-master\\datasets\\coco128\\images\\train2017'  # 数据集文件夹路径

# 获取标签文件名列表
label_files = os.listdir(labels_folder)

# 遍历数据集文件夹中的所有文件
for filename in os.listdir(data_folder):

    # 只处理图像文件
    if filename.endswith('.jpg') or filename.endswith('.jpeg') or filename.endswith('.png'):

        # 获取图像文件名对应的标签文件名
        label_filename = os.path.splitext(filename)[0] + '.txt'

        # 如果标签文件不存在，则删除图像文件
        if label_filename not in label_files:
            os.remove(os.path.join(data_folder, filename))