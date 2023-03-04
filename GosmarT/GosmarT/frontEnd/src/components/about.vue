<template>
  <div id="Footer">
    <p>{{ msg }}</p>
    <p>{{ detail }}</p>
  </div>
</template>

<script>
export default {
  name: 'about',
  data(){
    return{
      msg:'find more about the project @ https://github.com/ZhefeiGong',
      detail:'or @ gonzalez_zhefei@163.com',
    }
  }
}

</script>

<style scoped>
#Footer {
  /*background:#F2F6FC;*/
  padding: 6px;
  border-radius: 5px;
  width: 80%;
  height: 80px;
  margin: 20px auto;
  margin-top: 140px;
}

p {
  color: #626f70;
  text-align: center;
  margin: 30px auto;
  font-size: 1.1em;
}

</style>
