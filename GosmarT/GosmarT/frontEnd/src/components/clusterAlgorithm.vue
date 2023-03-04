<!--聚类算法Page-->
<template>
<!--title-->
<el-card class="title">
   <el-icon><Scissor /></el-icon>
   聚类算法图像分割
</el-card>

<el-card class="imageCard">
  <div class="leftPic">
              <el-image
                :src="submitUrl"
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
                :src="ansUrl"
                class="image"
                style="border-radius: 3px 3px 0 0"
              >
              </el-image>
            <div class="img_info" style="border-radius: 0 0 5px 5px">
              <span style="color: white; letter-spacing: 4px">分割结果</span>
            </div>
  </div>

</el-card>

<el-card class="buttonCard">
  <el-card class="buttonClass">
   <input  name="upload" type="file" style="background-color:back;color:white"   accept="image/png,image/gif,image/jpeg" id="imgFile" @change="changePic"/> 
  </el-card>
  <el-card class="buttonClass">
  <el-button v-show="isShow" type="success" plain v-on:click="segSubmit">开始分割
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
   <el-table class="table"
    :data="segInfor" style="width: 100%;">
   <el-table-column prop="time" label="耗时/s" width="360" />
   <el-table-column prop="count" label="迭代次数" width="360" />
   <el-table-column prop="scale" label="缩小比例" />
   </el-table>
</el-card>
</template>

<script>
import axios from "axios";
import { ElMessage } from 'element-plus'

export default {
  name: 'clusterAlgorithm',
  data(){
    return{

      baseUrl:'http://127.0.0.1:5000',

      // 聚类显示
      sitesAnsUrl:'src/assets/logo.png',
      sitesInfor:{
        randomNum:50,
        clusterNum:4
      },

      // 图像分割
      segtPic:{},
      submitUrl:'',
      ansUrl:'',
      isSegInforShow:false,
      segInfor:[],
      isShow:false,
      progressShow:false,

    }
  },
  methods:{

    // 图像分割
    segSubmit(){
      let that = this;
      that.segInfor=[];
      that.progressShow = true;
      let param = new FormData();
      param.append('picFile', that.segtPic, that.segtPic.name);
      axios({
           method: 'POST',
           url:that.baseUrl+'/KMsegPic',
           headers: {'Content-Type': 'multipart/form-data'},
           data: param,
           responseType: 'blob'
           })
          .then((response1) => {
            console.log(response1.data)
            that.ansUrl= window.URL.createObjectURL(response1.data)      // 后端返回前端渲染

            // 获取计算数据
            axios({
	           	method: 'GET',
		          url: that.baseUrl+'/KMsegData',
            })
            .then((response2)=>{
              that.segInfor.push(response2.data.data);
              console.log('获取KMsegData',response2.data.code);
            })
            .catch((error)=>{
              alert("KMsegDateError"+error);
            })
            that.ansUrl= window.URL.createObjectURL(response1.data)     // 后端返回前端渲染
            // 数据获取结束
            console.log('获取KMsegPic','success')
            that.showDone();
            that.progressShow = false;
        })
	        .catch((error) => {
         		  alert("KMsegPicError"+error);
        })
    },
    // 改变图像
    changePic(e){
      let that = this
      that.segtPic = e.target.files[0];
      that.submitUrl =  window.URL.createObjectURL(e.target.files[0]);
      that.isShow=true;
      console.log(that.segtPic.name);
      that.showChange()
    },
    // 聚类演示
    sitesSubmin(){
      let that = this;
      axios({
           method: 'POST',
           url:that.baseUrl+'/KMsites',
           //headers: {'Content-Type': 'multipart/form-data'},
           data: {
             'randomNum': that.sitesInfor.randomNum,
             'clusterNum': that.sitesInfor.clusterNum
           },
           responseType: 'blob'
           })
          .then((response) => {
            that.sitesAnsUrl= window.URL.createObjectURL(response.data);     // 后端返回前端渲染
            console.log('获取KMsites','success         ');                   // 数据获取结束
        })
	        .catch((error) => {
         		  alert("KMsitesError"+error);
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
    // 展示分割结束提示
    showDone(){
    ElMessage({
    duration:1500,
    message: 'segment over ^_^',
    type: 'success',
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
  color: #DFFFFF;
  background-color: #001A07;
  display: flex;
  padding:20px;
  width:200px;
  margin:0 auto;
  width: 1000px;
  justify-content: center;
}

.imageCard{
  background-color: #001A07;
  display: flex;
  padding:20px;
  width:200px;
  margin:0 auto;
  height: 525px;
  width: 1000px;
  justify-content: center;
}

.buttonCard{
  background-color: #001A07;
  display: flex;
  padding:20px;
  width: 1000px;
  margin:0 auto;
  justify-content: center;
  text-align: center;
}

.progressCard{
  background-color: #001A07;
  width: 1040px;
  margin:0 auto;
   justify-content: center;
  text-align: center;
}

.ansCard{
  background-color: #001A07;
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
  background-color: #014b15;
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
  background-color: #047a23;
}
</style>
