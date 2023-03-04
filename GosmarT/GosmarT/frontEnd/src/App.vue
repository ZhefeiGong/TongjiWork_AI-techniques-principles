<template>
  <!--导航栏-->
  <el-menu
    router
    :default-active="$route.path"
    class="el-menu-demo"
    mode="horizontal"
    background-color="#010131"
    text-color="#CBCACC"
    active-text-color="#CBF9F9"
    @select="handleSelect">

        <el-menu-item index="/">
         <el-icon><Orange /></el-icon>
          <span>GosmarT</span>
        </el-menu-item>
        
        <div class="flex-grow" />

        <el-menu-item index="/clusterAlgorithm">
          <el-icon><Scissor /></el-icon>
          <span>图像分割</span>
        </el-menu-item>

    
        <el-menu-item index="/linearSort">
          <el-icon><View /></el-icon>
          <span>线性分类</span>
        </el-menu-item>


        <el-menu-item index="/neuralNetwork">
          <el-icon><Share  /></el-icon>
          <span>目标检测</span>
        </el-menu-item>

        <el-menu-item index="/maskDetect">
          <el-icon><WalletFilled /></el-icon>
          <span>口罩检测</span>
        </el-menu-item>

        <el-menu-item index="/about">
          <el-icon><User /></el-icon>
          <span>about</span>
        </el-menu-item>

  </el-menu>

  <!--主要内容-->
  <el-main>
      <router-view></router-view>
  </el-main>

</template>

<script>
export default {
  name: 'App',
  components: {
  },
  mounted(){},
  methods: {
     handleSelect(key, keyPath) {
      console.log(key, keyPath);
    }
  },
  //实例创建之前钩子函数--给body添加行内样式
  beforeCreate () {
    this.$nextTick(()=>{
      document.body.setAttribute('style', 'background:#00021A')
    })
  },
  //实例销毁之前钩子--移除body 标签的属性style
  beforeDestroy () {
    document.body.removeAttribute('style')
  }
}
</script>

<!-- Add "scoped" attribute to limit CSS to this component only -->
<style scoped>
.flex-grow {
  flex-grow: 1;
}
.Header{
  color: #21b3b9; font-weight: bold
}

</style>
