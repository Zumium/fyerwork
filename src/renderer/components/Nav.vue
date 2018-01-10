 <template>
 <div class="nav">
    <el-menu
    default-active="2"
    class="el-menu-vertical-demo"
    background-color="#545c64"
    text-color="#fff"
    active-text-color="#ffd04b"
    router>
<!--     <el-menu-item index="folder">
      <i class="el-icon-menu"></i>
      <span slot="title">文件</span>
    </el-menu-item> -->
    <el-menu-item index="upload">
      <i class="el-icon-menu"></i>
      <span slot="title">上传</span>
    </el-menu-item>
    <el-menu-item index="download">
      <i class="el-icon-setting"></i>
      <span slot="title">下载</span>
    </el-menu-item>
  </el-menu>
</div>
</template>
<style scoped>
  .nav {
    width: 250px;
    height: 100vh;
    background-color: #545c64;
    float: left;
   }
</style>
<script>
  export default {
    name: 'Nav',
    methods: {
    }
  }
</script>
