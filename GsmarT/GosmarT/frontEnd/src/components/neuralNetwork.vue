<!--神经网路Page-->
<template>

<el-card class="title">
   <el-icon><Share  /></el-icon>
   目标检测COCO
</el-card>

<el-card class="imageCard">
  <div class="leftPic">
              <el-image
                :src="uploadUrl"
                class="image"
                style="border-radius: 3px 3px 0 0"
              >
              </el-image>
            <div class="img_info" style="border-radius: 0 0 5px 5px">
              <span style="color: white; letter-spacing: 4px">待测图像</span>
            </div>
  </div>

  <div class="rightPic">
              <el-image
                :src="detectAnsUrl"
                class="image"
                style="border-radius: 3px 3px 0 0"
              >
              </el-image>
            <div class="img_info" style="border-radius: 0 0 5px 5px">
              <span style="color: white; letter-spacing: 4px">检测结果</span>
            </div>
  </div>

</el-card>

<el-card class="buttonCard">
  <el-card class="buttonClass">
   <input  name="upload" type="file" style="background-color:back;color:white"   accept="image/png,image/gif,image/jpeg" id="imgFile" @change="changePic"/> 
  </el-card>
  <el-card class="buttonClass">
  <el-button v-show="isShow" type="success" plain v-on:click="detectSubmit">开始检测
  </el-button>
  </el-card>

</el-card>
<el-card class="progressCard">
 <el-progress v-show="progressShow"
      :percentage="100"
      status="success"
      :indeterminate="true"
      :duration="5"
    />
</el-card>
<el-card class="ansCard">
    <el-table class="table" :data="detectData" stripe style="width: 100%">
       <el-table-column prop="site" label="中心坐标" width="270" />
       <el-table-column prop="type" label="类别" width="270" />
       <el-table-column prop="area" label="区域大小" width="270" />
       <el-table-column prop="value" label="置信度" />
    </el-table>
</el-card>

</template>

<script>
import axios from "axios";
import { ElMessage } from 'element-plus';

export default{
 name: 'neuralNetwork',
 data(){
    return{
      baseUrl:'http://127.0.0.1:5000',

      // 检测
      uploadUrl:'',
      detectAnsUrl:'',
      detectPic:{},
      detectData:[],
      isShow:false,
      progressShow:false,
    }

  },
  methods:{
    // 选择上传图像
    changePic(e){
       let that = this
       that.detectPic = e.target.files[0];
       that.uploadUrl =  window.URL.createObjectURL(e.target.files[0]);
       that.isShow=true;
       console.log(that.detectPic.name);
       that.showChange();
    },
    // 上传图像并识别
    detectSubmit(){
      let that = this;
      that.progressShow = true;
      let param = new FormData();
      param.append('picFile', that.detectPic, that.detectPic.name);
      axios({
           method: 'POST',
           url:that.baseUrl+'/YLdetect_coco',
           headers: {'Content-Type': 'multipart/form-data'},
           data: param,
           responseType: 'blob'
           })
          .then((response) => {
            that.detectDataGet()
            that.detectAnsUrl= window.URL.createObjectURL(response.data)      // 后端返回前端渲染
            // 数据获取结束
            console.log('获取YLdetect_coco','success')
            that.progressShow = false;
        })
	        .catch((error) => {
            that.progressShow = false;
         		alert("YLdetect_cocoError"+error);
        })
    },
    // 获取产生的数据
    detectDataGet(){
      let that = this
      axios({
	            method: 'GET',
		          url: that.baseUrl + '/YLgetdata_coco',
          })
	            .then((response) => {
              that.detectData = response.data.predictData;
              console.log(that.detectData)
              that.showDone();
          })
	            .catch((error) => {
              console.log(error);
              that.detectData = 0;
         		  console.log("sorry, we detect nothing +_+");
              that.showNone()
        	})
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
    // 展示分割结束提示
    showNone(){
    ElMessage({
    duration:1500,
    message: 'Sorry, we detect nothing +_+',
    type: 'warning',
    })
    }
  }
}
</script>

<!-- Add "scoped" attribute to limit CSS to this component only -->
<style scoped>

.title{
  font:200;
  font-size: 50px;
  color: #FFDDDD;
  background-color: #1E0000;
  display: flex;
  padding:20px;
  width:200px;
  margin:0 auto;
  width: 1000px;
  justify-content: center;
}

.imageCard{
  background-color: #1E0000;
  display: flex;
  padding:20px;
  width:200px;
  margin:0 auto;
  height: 525px;
  width: 1000px;
  justify-content: center;
}

.buttonCard{
  background-color: #1E0000;
  display: flex;
  padding:20px;
  width: 1000px;
  margin:0 auto;
  justify-content: center;
  text-align: center;
}

.progressCard{
  background-color: #1E0000;
  width: 1040px;
  margin:0 auto;
   justify-content: center;
  text-align: center;
}

.ansCard{
  background-color: #1E0000;
  display: flex;
  padding:20px;
  width: 1000px;
  margin:0 auto;
  justify-content: center;
  text-align: center;
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
  background-color: #680000;
  line-height: 30px;
}

.leftPic{
  display:inline-block;
  margin-right: 15px;
}

.rightPic{
  display:inline-block;
  margin-left: 15px;
}

.buttonClass{
  height: 70px;
  width: 300px;
  text-align: center;
  display : inline-block;
  background-color: #AC0000;
}

</style>