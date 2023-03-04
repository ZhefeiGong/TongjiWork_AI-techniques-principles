# @time    : 2022.6.10--2022.6.16
# author   : gonzalez
# function : API接口文件

# 接口Package
from flask import Flask, request, send_file
from flask import jsonify
from flask_cors import CORS

# 功能实现Package
import KMeans.imageSegmentKMeans
import KMeans.gonKMeans
import Linear.gonSVM
import os
import shutil
import numpy as np


app = Flask(__name__)


##################################
# 图像分割任务
##################################
corSeg1 = CORS(app, resources={r"/KMsites": {"origins": "*"}})     # 跨域处理
corSeg2 = CORS(app, resources={r"/KMsegPic": {"origins": "*"}})     # 跨域处理
corSeg3 = CORS(app, resources={r"/KMsegData": {"origins": "*"}})     # 跨域处理
segTime = 0
segCount = 0
segScale = 0

# KMeans聚类可视化
@app.route('/KMsites', methods=['POST'])
def KMsites():
    data = request.get_json(silent=True)
    randomNum = data['randomNum']
    clusterNum = data['clusterNum']
    KMeans.gonKMeans.KMsitesWork(randomNum, clusterNum)
    return send_file('./KMeans/image/ansSites.jpg', mimetype='image/jpg')

# KMeans实现图像分割_图像返回
@app.route('/KMsegPic', methods=['POST'])
def KMsegPic():
    anchor = request.files['picFile']
    anchor.save('./KMeans/image/ori.jpg')
    time, count, scale = KMeans.imageSegmentKMeans.imageSeg() # 执行图像分割任务
    global segTime, segCount, segScale
    segTime = time
    segCount = count
    segScale = scale
    return send_file('./KMeans/image/ans.jpg', mimetype='image/jpg')

# KMeans实现图像分割_数据返回
@app.route('/KMsegData', methods=['GET'])
def KMsegData():
    getData = {'time': round(segTime, 2), 'count': segCount, 'scale': round(segScale,2)}
    response = {
        'data': getData,
        'code': 'success'
    }
    return response


##################################
# 线性分类任务
##################################
corLin1 = CORS(app, resources={r"/LTrain": {"origins": "*"}})       # 跨域处理
corLin2 = CORS(app, resources={r"/LTrainData": {"origins": "*"}})   # 跨域处理
corLin3 = CORS(app, resources={r"/LPredict": {"origins": "*"}})     # 跨域处理

svm = Linear.gonSVM.gonSVM()
accuracy = 0

# 进行训练
@app.route('/LTrain', methods=['POST'])
def LTrain():
    data = request.get_json(silent=True)
    learningRate = data['learningRate']
    alpha = data['alpha']
    epoch = data['epoch']
    global accuracy
    accuracy, xValue, yValue = Linear.gonSVM.linearTrain(svm, learningRate, alpha, epoch) # 开始进行训练
    response = {
        'xValue': xValue,
        'yValue': yValue,
        'code': 'success'
    }
    return jsonify(response)

# 获取最终准确率
@app.route('/LTrainData', methods=['GET'])
def LTrainData():
    global accuracy
    response = {
        'accuracy': round(accuracy, 2),
        'code': 'success'
    }
    return jsonify(response)

# 进行预测
@app.route('/LPredict', methods=['POST'])
def LPredict():
    anchor = request.files['picFile']
    anchor.save('./Linear/image/ori.jpg')
    ans = Linear.gonSVM.linearPredict(svm) # 开始进行预测
    response = {
        'predict': str(ans[0]),
        'code': 'success'
    }
    return jsonify(response)


##################################
# YOLOv5目标检测
##################################
corYolo1 = CORS(app, resources={r"/YLdetect_coco": {"origins": "*"}})         # 跨域处理
corYolo2 = CORS(app, resources={r"/YLgetdata_coco": {"origins": "*"}})        # 跨域处理
corYolo3 = CORS(app, resources={r"/YLdetect_mask": {"origins": "*"}})         # 跨域处理
corYolo4 = CORS(app, resources={r"/YLgetdata_mask": {"origins": "*"}})        # 跨域处理
signsCOCO = ['person', 'bicycle', 'car', 'motorcycle', 'airplane', 'bus', 'train', 'truck', 'boat', 'traffic light',
             'fire hydrant', 'stop sign', 'parking meter', 'bench', 'bird', 'cat', 'dog', 'horse', 'sheep', 'cow',
             'elephant', 'bear', 'zebra', 'giraffe', 'backpack', 'umbrella', 'handbag', 'tie', 'suitcase', 'frisbee',
             'skis', 'snowboard', 'sports ball', 'kite', 'baseball bat', 'baseball glove', 'skateboard', 'surfboard',
             'tennis racket', 'bottle', 'wine glass', 'cup', 'fork', 'knife', 'spoon', 'bowl', 'banana', 'apple',
             'sandwich', 'orange', 'broccoli', 'carrot', 'hot dog', 'pizza', 'donut', 'cake', 'chair', 'couch',
             'potted plant', 'bed', 'dining table', 'toilet', 'tv', 'laptop', 'mouse', 'remote', 'keyboard',
             'cell phone',
             'microwave', 'oven', 'toaster', 'sink', 'refrigerator', 'book', 'clock', 'vase', 'scissors', 'teddy bear',
             'hair drier', 'toothbrush']
signsMASK = ['unmasked', 'masking']

# 输入图片进行coco预测
@app.route('/YLdetect_coco', methods=['POST'])
def YLdetect_coco():
    anchor = request.files['picFile']
    anchor.save('./yolov5/data/images/detect_coco.jpg')
    shutil.rmtree('yolov5/runs/detect/exp')
    os.system('python yolov5/detect.py --source yolov5/data/images/detect_coco.jpg --weights yolov5/weights/coco.pt')   # 执行coco数据集预测任务
    return send_file('./yolov5/runs/detect/exp/detect_coco.jpg', mimetype='image/jpg')

# 获取预测结果数据
@app.route('/YLgetdata_coco', methods=['GET'])
def YLgetdata_coco():
    global signsCOCO
    dataGet = np.loadtxt('yolov5/runs/detect/exp/labels/detect_coco.txt', dtype=np.float64)
    dataGet = np.round(dataGet, 2)
    if dataGet.ndim == 1:
        dataGet.resize((1, 6))
    data = []
    for i in range(len(dataGet)):
        temp = {'site': '( '+(str(round(dataGet[i][1], 2)) + ' , ' + str(round(dataGet[i][2], 2))+' )'),
                'type': signsCOCO[int(dataGet[i][0])],
                'area': round(dataGet[i][3] * dataGet[i][4], 6), 'value': round(dataGet[i][5], 2)}
        data.append(temp)
    response = {
        'predictData': data,
        'code': 'success'
    }
    return response

# 输入照片进行mask预测
@app.route('/YLdetect_mask', methods=['POST'])
def YLdetect_mask():
    anchor = request.files['picFile']
    anchor.save('./yolov5/data/images/detect_mask.jpg')
    shutil.rmtree('yolov5/runs/detect/exp')
    os.system('python yolov5/detect.py --source yolov5/data/images/detect_mask.jpg --weights yolov5/weights/mask.pt') # 执行mask数据集预测任务
    return send_file('./yolov5/runs/detect/exp/detect_mask.jpg', mimetype='image/jpg')

# 获取预测结果数据
@app.route('/YLgetdata_mask', methods=['GET'])
def YLgetdata_mask():
    global signsMASK
    dataGet = np.loadtxt('yolov5/runs/detect/exp/labels/detect_mask.txt', dtype=np.float64)
    dataGet = np.round(dataGet, 2)
    if dataGet.ndim == 1:
        dataGet.resize((1, 6))
    data = []
    for i in range(len(dataGet)):
        temp = {'site': '( ' + (str(round(dataGet[i][1], 2)) + ' , ' + str(round(dataGet[i][2], 2)) + ' )'),
                'type': signsMASK[int(dataGet[i][0])],
                'area': round(dataGet[i][3] * dataGet[i][4], 6), 'value': round(dataGet[i][5], 2)}
        data.append(temp)
    response = {
        'predictData': data,
        'code': 'success'
    }
    return response



# 启动运行
if __name__ == '__main__':
     app.run()



