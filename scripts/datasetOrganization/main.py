import fileinput
import glob
import os
import shutil
import random


# # 设置工作目录
# work_dir = "C:\\Users\\30235\\Desktop\\parking2\\valid"
#
# # 获取当前目录下所有的图片文件名
# img_files = [f for f in os.listdir(os.path.join(work_dir, "images")) if os.path.isfile(os.path.join(work_dir, "images", f))]
#
# # 重命名图片文件名
# for i, img_file in enumerate(img_files):
#     # 构造新的文件名
#     new_img_name = str(i) + os.path.splitext(img_file)[1]
#     # 重命名图片文件
#     os.rename(os.path.join(work_dir, "images", img_file), os.path.join(work_dir, "images", new_img_name))
#     # 获取对应标签文件名
#     label_file = os.path.join(work_dir, "labels", os.path.splitext(img_file)[0] + ".txt")
#     # 如果标签文件存在，则对标签文件进行重命名
#     if os.path.isfile(label_file):
#         new_label_name = str(i) + ".txt"
#         os.rename(label_file, os.path.join(work_dir, "labels", new_label_name))
#
# print("Done.")


#
# # 设置工作目录和增加的数字
# work_dir = "C:\\Users\\30235\\Desktop\\parking1\\train\\images"
# add_number = 1
#
# # 遍历目录下的文件
# for filename in os.listdir(work_dir):
#     # 获取文件名和文件扩展名
#     basename, ext = os.path.splitext(filename)
#     # 检查文件名除去后缀是否为数字
#     if basename.isdigit():
#         # 将文件名转换为整数，并加上增加的数字
#         new_number = int(basename) + add_number
#         # 构造新的文件名
#         new_filename = str(new_number) + ext
#         # 重命名文件
#         os.rename(os.path.join(work_dir, filename), os.path.join(work_dir, new_filename))
#
# print("Done.")


# # 设置工作目录和标签文件扩展名
# work_dir = "C:\\Users\\30235\\Desktop\\parking1\\train\\labels"
# ext = ".txt"
#
# # 遍历目录下的标签文件
# for filename in os.listdir(work_dir):
#     # 检查文件是否为标签文件
#     if filename.endswith(ext):
#         # 打开文件并读取所有行
#         filepath = os.path.join(work_dir, filename)
#         with fileinput.input(files=(filepath), inplace=True) as f:
#             for line in f:
#                 # 将标签id为2的改成1，其余不变
#                 values = line.strip().split()
#                 if len(values) > 0 and int(values[0]) == 1:
#                     values[0] = "0"
#                     print(" ".join(values))
#                 # 删除标签id为1的那行
#                 elif len(values) > 0 and int(values[0]) == 0:
#                     values[0] = "1"
#                     print(" ".join(values))
#
# print("Done.")

# # 设置工作目录和标签文件、图片文件所在的目录和扩展名
# label_dir = "C:\\Users\\30235\\Desktop\\ultralytics-main\\datasets\\parking2\\train\\labels"
# image_dir = "C:\\Users\\30235\\Desktop\\ultralytics-main\\datasets\\parking2\\train\\images"
# label_ext = ".txt"
# image_ext = ".jpg"


# # 遍历标签文件所在的目录
# for filename in glob.glob(os.path.join(label_dir, "*" + label_ext)):
#     # 打开文件并读取所有行
#     with open(filename, "r") as f:
#         lines = f.readlines()
#
#     # # 如果行值多余5的行，删除标签文件并删除对应的同名图片文件
#     # if any(len(line.strip().split()) > 5 for line in lines):
#     #     os.remove(filename)
#     #     basename = os.path.splitext(os.path.basename(filename))[0]
#     #     img_path = os.path.join(image_dir, basename + image_ext)
#     #     if os.path.exists(img_path):
#     #         os.remove(img_path)
#     #     continue
#
#     # 修改标签文件内容
#     new_lines = []
#     for line in lines:
#         # 将标签id为2的改成1，将标签id为1的那行删除
#         values = line.strip().split()
#         if len(values) > 0 and int(values[0]) == 2:
#             values[0] = "1"
#             new_lines.append(" ".join(values) + "\n")
#         elif len(values) > 0 and int(values[0]) != 1:
#             new_lines.append(line)
#
#     # 如果修改后的内容为空，删除标签文件并删除对应的同名图片文件
#     if len(new_lines) == 0:
#         os.remove(filename)
#         basename = os.path.splitext(os.path.basename(filename))[0]
#         img_path = os.path.join(image_dir, basename + image_ext)
#         if os.path.exists(img_path):
#             os.remove(img_path)
#     # 否则，将修改后的内容写回文件中
#     else:
#         with open(filename, "w") as f:
#             f.writelines(new_lines)
#
# print("Done.")



# # 设置工作目录和训练集、验证集图片和标签文件所在的目录和扩展名
# train_image_dir = "C:\\Users\\30235\\Desktop\\ultralytics-main\\datasets\\parking_high\\train\\images"
# train_label_dir = "C:\\Users\\30235\\Desktop\\ultralytics-main\\datasets\\parking_high\\train\\labels"
# val_image_dir = "C:\\Users\\30235\\Desktop\\ultralytics-main\\datasets\\parking_high\\valid\\images"
# val_label_dir = "C:\\Users\\30235\\Desktop\\ultralytics-main\\datasets\\parking_high\\valid\\labels"
# image_ext = ".jpg"
# label_ext = ".txt"
#
# # 获取验证集中的所有图片文件名
# val_images = set(os.path.splitext(os.path.basename(f))[0] for f in glob.glob(os.path.join(val_image_dir, "*" + image_ext)))
#
# # 遍历训练集中的所有图片文件
# for filename in glob.glob(os.path.join(train_image_dir, "*" + image_ext)):
#     # 如果训练集中的图片文件名与验证集中的图片文件名相同，则删除训练集中的图片文件和标签文件
#     basename = os.path.splitext(os.path.basename(filename))[0]
#     if basename in val_images:
#         os.remove(filename)
#         label_path = os.path.join(train_label_dir, basename + label_ext)
#         if os.path.exists(label_path):
#             os.remove(label_path)
#
# print("Done.")




# 设置随机数种子
random.seed(123)

# 数据集路径
data_dir = "C:\\Users\\30235\\Desktop\\parking_final"


# 划分比例
split_ratio = 0.2

# 获取文件列表
images_dir = os.path.join(data_dir, "train", "images")
labels_dir = os.path.join(data_dir, "train", "labels")
images_list = os.listdir(images_dir)

# 随机打乱文件列表
random.shuffle(images_list)

# 计算划分点
split_index = int(len(images_list) * split_ratio)

# 划分数据集
val_images_dir = os.path.join(data_dir, "val", "images")
val_labels_dir = os.path.join(data_dir, "val", "labels")
if not os.path.exists(val_images_dir):
    os.makedirs(val_images_dir)
if not os.path.exists(val_labels_dir):
    os.makedirs(val_labels_dir)

for i in range(split_index):
    image_name = images_list[i]
    label_name = os.path.splitext(image_name)[0] + ".txt"
    shutil.move(os.path.join(images_dir, image_name), os.path.join(val_images_dir, image_name))
    shutil.move(os.path.join(labels_dir, label_name), os.path.join(val_labels_dir, label_name))