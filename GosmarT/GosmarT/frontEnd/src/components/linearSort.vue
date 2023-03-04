<!--线性分类Page-->
<template>
<!--title-->
<el-card class="title">
  <el-icon><View /></el-icon>
  支持向量机线性分类
</el-card>
    
<!--训练-->
    <el-card class="box-card">
        <el-card class="inputCard">
        <el-input-number v-model="parameter.learningRate" size="large" :precision="9" :step="0.000000005" :max="0.0001" :min="0.000000001" />
        <div class="textStyle">
          learning rate
        </div>
        </el-card>
         <el-card class="inputCard">
        <el-input-number v-model="parameter.alpha" size="large" :precision="2" :step="100" :max="100000" />
         <div class="textStyle">
          alpha value
        </div>
        </el-card>
        <el-card class="inputCard">
        <el-input-number v-model="parameter.epoch" size="large" :precision="0" :step="10" :min="500"  :max="5000" />
         <div class="textStyle">
          epoch value
        </div>
        </el-card>
    </el-card>

    <el-card class="box-card">
      <el-card class="inputCard">
        <el-button type="success" plain @click="trainSubmit">开始训练</el-button>
      </el-card>
    </el-card>
 
  <el-card class="imageCard">
  <div class="Pic">
            <div id="trainChart" class="graph"></div>
            <div class="img_info" style="border-radius: 0 0 5px 5px">
              <span style="color: white; letter-spacing: 4px">训练结果{{accuracyShow}}</span>
            </div>
  </div>

  <div class="Pic">
              <el-image
                :src="predictUrl"
                class="image"
                style="border-radius: 3px 3px 0 0"
              >
              </el-image>
            <div class="img_info" style="border-radius: 0 0 5px 5px">
              <span style="color: white; letter-spacing: 4px">待测图像</span>
            </div>
  </div>

</el-card>

    <el-card v-show="progressShow" class="progressCard">
        <el-progress 
          :percentage="100"
          status="success"
          :indeterminate="true"
          :duration="5"
        />
     </el-card>

<!--预测-->
<el-card v-show="buttonShow" class="buttonCard">
  <el-card class="buttonClass">
   <input  name="upload" type="file" style="background-color:back;color:white"   accept="image/png,image/gif,image/jpeg" id="imgFile" @change="changePic"/> 
  </el-card>
  <el-card class="buttonClass">
  <el-button v-show="preShow" type="success" plain @click="predictSubmit">开始检测</el-button>
  </el-card>
</el-card>

<el-card  v-show="buttonShow" class="buttonCard">
   <el-card class="predictClass">
  <text class="ansStyle">
    预测结果为：{{items[predictAns]}}
  </text>
   </el-card>
</el-card>
</template>


<script>
import axios from "axios";
import { ElMessage } from 'element-plus';
import * as echarts from 'echarts'

export default {
  name: 'linearSort',
  data(){
    return{

      baseUrl:'http://127.0.0.1:5000',

      // 训练
      trainXValue:[],
      trainYvalue:[],
      trainAccuracy:'',
      accuracyShow:'',
      parameter:{
        learningRate:1e-7,
        alpha:5e3, 
        epoch:3000
      },

      progressShow:false,
      buttonShow :false,
      preShow:false,

      // 预测
      predictUrl:'',
      predictAns:'',
      predictPic:{},
      items:['airplane','automobile','bird','cat','deer','dog','frog','horse','ship','truck']
      
    }
  },
  methods:{
    // 训练提交数据
    trainSubmit(){
      let that = this;
      that.progressShow = true;
      axios({
           method: 'POST',
           url:that.baseUrl+'/LTrain',
           data: {
             'learningRate': that.parameter.learningRate,
             'alpha': that.parameter.alpha,
             'epoch':that.parameter.epoch
           },
           })
          .then((response1) => {
            that.trainXValue = response1.data.xValue;
            that.trainYvalue = response1.data.yValue;
            // 获取数据
            axios({
	            method: 'GET',
		          url: that.baseUrl+'/LTrainData',
            })
	          .then((response2) => {
              that.trainAccuracy = response2.data.accuracy
              that.accuracyShow = '(Accuracy:'+(that.trainAccuracy).toString()+'%)';
              console.log('获取LTrainData',response2.data.code);    
            })
	          .catch((error) => {
          	  alert("LTrainDataError"+error);
          	})
            that.showGraph();// 展示曲线信息
            // 数据获取结束
            console.log('获取LTrain',response1.data.code); 
            that.progressShow = false;
            that.buttonShow  = true; 
            that.showFinish();
        })
	        .catch((error) => {
         		alert("LTrainError"+error);
            that.progressShow = false;
        })
    },

    // 测试提交数据
    predictSubmit(){
      let that = this
      //that.progressShow = true;
      let param = new FormData();
      param.append('picFile', that.predictPic, that.predictPic.name);
      axios({
        method: 'POST',
        url:  that.baseUrl+'/LPredict',
        headers: {'Content-Type': 'multipart/form-data'},
        data: param
      })
      .then((response) => {
        that.predictAns = response.data.predict
        console.log('获取LPredict',response.data.code)
        that.showDone();
        //that.progressShow = false;
      })
	    .catch((error) => {
        alert("LPredictError"+error);
        //that.progressShow = false;
      })
    },

    //照片提交更改
    changePic(e){
       let that = this
       that.predictPic = e.target.files[0];
       that.predictUrl =  window.URL.createObjectURL(e.target.files[0]);
       console.log(that.predictPic.name);
       that.preShow=true;
       that.showChange();
    },

    // 展示选择成功提示
    showChange(){
    ElMessage({
    duration:1500,
    message: 'Selet success',
    type: 'success',
    })
    },

    // 展示检测结束提示
    showDone(){
    ElMessage({
    duration:1500,
    message: 'Detect over ^_^',
    type: 'success',
    })
    },

    // 展示检测结束提示
    showFinish(){
    ElMessage({
    duration:1500,
    message: 'Train over ^_^',
    type: 'success',
    })
    },

    // 展示分割结束提示
    showNone(){
    ElMessage({
    duration:1500,
    message: 'Sorry, we detect nothing +_+',
    type: 'warning',
    })
    },

    //展示图像
    showGraph(){
      let that = this;
      let myChart = echarts.init(document.getElementById("trainChart"));
      // 绘制图表
      myChart.setOption({
        xAxis: {
          data:that.trainXValue
        },
        yAxis:{},
        series: [
          {
            name: "Loss Value",
            type: "line",
            data: that.trainYvalue
          }
        ]
      });
      window.onresize = function () { // 自适应大小
        myChart.resize();
      };
    }

  }
}
</script>


<style scoped>
.title{
  font:200;
  font-size: 50px;
  color: #ebe3f2;
  background-color: #18002A;
  display: flex;
  padding:20px;
  width:200px;
  margin:0 auto;
  width: 1000px;
  justify-content: center;
}

.box-card{
  background-color: #18002A;
  display: flex;
  padding:20px;
  width: 1000px;
  margin:0 auto;
  justify-content: center;
  text-align: center;
}

.inputCard{
  height: auto;
  width: auto;
  text-align: center;
  display : inline-block;
  background-color: #6c17ad;
}

.textStyle{
  color: aliceblue;
  text-align: center;
}

.imageCard{
  background-color: #18002A;
  display: flex;
  padding:20px;
  width:200px;
  margin:0 auto;
  height: 525px;
  width: 1000px;
  justify-content: center;
}
.Pic{
  display:inline-block;
  margin-right: 15px;
}
.image {
  width: 450px;
  height: 450px;
  background: #ffffff;
  box-shadow: 0 2px 12px 0 rgba(0, 0, 0, 0.1);
}

.img_info {
  height: 30px;
  width: 450px;
  text-align: center;
  background-color: #400070;
  line-height: 30px;
}

.buttonCard{
  background-color: #18002A;
  display: flex;
  padding:20px;
  width: 1000px;
  margin:0 auto;
  justify-content: center;
  text-align: center;
}

.buttonClass{
  height: 70px;
  width: 300px;
  text-align: center;
  display : inline-block;
  background-color: #6c17ad;
}

.predictClass{
  height: 70px;
  width: 600px;
  text-align: center;
  display : inline-block;
  background-color: #6c17ad;
}

.progressCard{
  background-color: #18002A;
  width: 1040px;
  margin:0 auto;
   justify-content: center;
  text-align: center;
}

.ansStyle{
  color: white;
  text-align: center;
  font-size: 25px;
}

.graph{
  width: 450px;
  height: 455px;
  background-color:rgb(253, 249, 253) ;
  border-radius: 3px 3px 0 0;
  box-shadow: 0 2px 12px 0 rgba(0, 0, 0, 0.1);
}
</style>
