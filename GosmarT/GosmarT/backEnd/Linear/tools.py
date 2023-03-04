# @author   : gonzalez
# @time     : 2022.5.19
# @function : 实现数据集处理的函数

import pickle
import numpy as np
import matplotlib.pyplot as plt
import cv2

# @function  : 产生针对KNN进行数据裁切后的数据集
# @parameter : ...
def datasetGet(ratioTrain = 0, ratioTest = 0, ratioVerify = 0, verifyNum = 5):

    # 生成训练集
    trainFileNum = 5                                                      # 数据集总个数
    trainData = []                                                        # 训练集数据
    trainLabels = []                                                      # 训练集标记
    for i in range(trainFileNum):                                         # 文件遍历
        if i+1 != verifyNum:                                              # 验证集选择
            trainFile = open('./Linear/cifar10/data_batch_' + str(i+1), 'rb')    # 打开训练集文件
            trainFileData = pickle.load(trainFile, encoding='bytes')      # 存储为字典格式
            count = 0                                                     # 计数参数
            for each in trainFileData[b'data']:                           # 数据遍历
                count += 1                                                # 计算参数
                if ratioTrain != 0:                                       # 需要进行训练集分割
                    if count % ratioTrain == 0:                           # 训练集ratio
                        trainData.append(each)                            # 训练集添加
                else:                                                     # 所有cifar10添加
                    trainData.append(each)                                # 数据添加
            count = 0                                                     # 计数参数
            for each in trainFileData[b'labels']:                         # 标签遍历
                count += 1                                                # 计数参数
                if ratioTrain != 0:                                       # 需要进行训练集分割
                    if count % ratioTrain == 0:                           # 训练集ratio
                        trainLabels.append(each)                          # 训练集标签添加
                else:                                                     # 所有cifar10添加
                    trainLabels.append(each)                              # 数据添加

    # 验证集
    verifyData = []
    verifyLabels = []
    verifyFile = open('./Linear/cifar10/data_batch_'+str(verifyNum), 'rb')       # 打开测试集文件
    verifyFileData = pickle.load(verifyFile, encoding='bytes')            # 存储为字典格式
    count = 0
    for each in verifyFileData[b'data']:
        count += 1
        if ratioVerify != 0:                                              # 需要进行验证集分割
            if count % ratioVerify == 0:                                  # 验证集ratio
                verifyData.append(each)                                   # 验证集数据添加
        else:
            verifyData.append(each)
    count = 0
    for each in verifyFileData[b'labels']:
        count += 1                                                        # 用于计数
        if ratioVerify != 0:                                              # 需要进行验证集分割
            if count % ratioVerify == 0:                                  # 验证集ratio
                verifyLabels.append(each)                                 # 验证集标签添加
        else:
            verifyLabels.append(each)

    # 生成测试集
    testData = []
    testLabels = []
    testFile = open('./Linear/cifar10/test_batch', 'rb')                         # 打开测试集文件
    testFileData = pickle.load(testFile, encoding='bytes')                # 存储为字典格式
    count = 0
    for each in testFileData[b'data']:
        count += 1
        if ratioTest != 0:                                                # 需要进行测试集分割
            if count % ratioTest == 0:                                    # 测试集ratio
                testData.append(each)                                     # 测试集数据添加
        else:
            testData.append(each)
    count = 0
    for each in testFileData[b'labels']:
        count += 1
        if ratioTest != 0:
            if count % ratioTest == 0:
                testLabels.append(each)
        else:
            testLabels.append(each)

    # 数据预处理
    trainData = np.array(trainData).astype('float32')                                       # 形成矩阵
    trainLabels = np.array(trainLabels)                                                     # 形成矩阵
    testData = np.array(testData).astype('float32')                                         # 形成矩阵
    testLabels = np.array(testLabels)                                                       # 形成矩阵
    verifyData = np.array(verifyData).astype('float32')                                     # 形成矩阵
    verifyLabels = np.array(verifyLabels)                                                   # 形成矩阵

    return trainData, trainLabels, testData, testLabels, verifyData, verifyLabels           # 返回数据集


# @function : 显示曲线图
def graphShow(x, y, xLable, yLable, mytitle):
    plt.title(mytitle)
    plt.plot(x, y)
    plt.xlabel(xLable)
    plt.ylabel(yLable)
    plt.savefig('./Linear/image/train.jpg')
    plt.close()


# @function : 显示散点图
def scatterShow(x, y, xLable, yLable, title):
    plt.title(title)
    plt.scatter(x, y)
    plt.xlabel(xLable)
    plt.ylabel(yLable)
    plt.show()


# @function : 数据预处理-->中心化+归一化-->Z-Score标准化处理
def ZScore(dataSet):
    length = len(dataSet)                 # 原始数据长度
    total = np.sum(dataSet, axis=0)       # 纵向求和
    ave = total.astype('float32')/length  # 均值
    dataTemp = np.zeros(dataSet.shape)    # 临时计算变量
    for i in range(length):               # 每个数据减去均值以求得方差
        dataTemp[i] = dataSet[i] - ave    # 减去均值
    dataTemp = dataTemp * dataTemp        # 数据平方
    dataT = np.sum(dataTemp, axis=0)      # 纵向求和
    for i in range(len(dataT)):           # 开方得标准差
        dataT[i] = pow(dataT[i], 0.5)     # 开方
    res = np.copy(dataSet)                # 深拷贝原始数据
    for i in range(length):               # 每隔数据执行
        res[i] = (dataSet[i]-ave)/dataT   # 进行Z-Score划分
    return res                            # 返回中心化数据


# @function : 数据中心化
def preProcessing(dataSet):
   return dataSet - np.mean(dataSet, axis=0) # 数据中心化


# @function : 数据维度转化
def dim3Todim2(res):
    get=[]
    for i in range(len(res)):
        for j in range(len(res[0])):
            for k in range(len(res[0][0])):
                get.append(res[i][j][k])
    get = np.array(get)
    return get.reshape((1, -1))



if __name__ == '__main__':

    image = cv2.imread('./image/ori.jpg')
    res = cv2.resize(image, (32, 32), interpolation=cv2.INTER_CUBIC)
    cv2.imshow('iker', res)

    test = dim3Todim2(res)
    print(len(test))
    print(len(test[0]))
    print(test)

    print(len(image))
    print(len(image[0]))

    cv2.imshow('image', image)
    cv2.imwrite('./image/test.png', res)  # 写入图片
    # cv2.destroyAllWindows()  # 关闭窗口
    cv2.waitKey(0)

