# @author    : gonzalez
# @time      : 2022.6.10
# @function  : 运用KMeans聚类算法实现图像分割
import matplotlib.pyplot as plt

from KMeans.toolFunction import *
from PIL import Image
from scipy import misc
import imageio
import time


# @function : KMeans执行图像分割任务
def imageSeg():
    segmentNum = 2                                                                         # 簇的个数
    featureMethod = featureColorPosition                                                   # 采用的特征提取方式
    ansImgPath = './KMeans/image/ans.jpg'                                                         # 结果图片存储
    oriImgPath = './KMeans/image/ori.jpg'                                                         # 处理图片
    originalImage = np.array(Image.open(oriImgPath))                                       # 打开原始图片
    scale = chooseScale(originalImage, 0)                                                  # 根据图片确定缩小比例
    # 执行聚类
    startTime = time.time()                                                                # 记录开始时间
    mask, count =segmentKmeans(originalImage, segmentNum, scale, featureMethod) # 调用聚类分割
    endTime = time.time()                                                                  # 记录结束时间
    imageio.imsave(ansImgPath, mask)                                                       # 保存图像
    return endTime-startTime, count, scale


if __name__ == "__main__":
    time, count, scale = imageSeg()
    print(time, ' ', count, ' ', scale)

