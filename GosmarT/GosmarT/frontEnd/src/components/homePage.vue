<!--首页信息-->
<template>
<el-card class="backCard">
  <el-image class="image" :src="picUrl"/>
</el-card>
</template>

<script>

export default {
  data(){
    return{
      picUrl:"src/assets/background.jpg"
    }
  }
}
</script>

<style scoped>
.backCard{
  width: 98%;
  height:100%;
  margin:0 auto;
  background-color: rgb(3, 0, 16);
}
.image{
  width: 100%;
  height:100%;
}

</style>