<template>
  <div class="container">
    <div class="upload">
      <!-- Zumium action中修改post的位置-->
      <el-upload
      class="upload-demo"
      action="https://jsonplaceholder.typicode.com/posts/"
      :headers="{'Access-Control-Allow-Origin': true}"
      :on-preview="handlePreview"
      :on-remove="handleRemove"
      :before-remove="beforeRemove"
      multiple
      :limit="3"
      :before-upload="handleBeforeUpload"
      :on-success="handleSuccess"
      :on-exceed="handleExceed"
      :on-error="handleError"
      :file-list="fileList">
      <el-button class="upload-button" size="small" type="primary">点击上传</el-button>
    </el-upload>
  </div>
</div>
</template>
<style>
  .container {
    margin-left: 250px;
  }
  div.cell {
    text-align: center;
  }
  .upload {
    text-align: center;
    padding: 100px;
  }
</style>
<script>
  export default {
    data () {
      return {
        fileList: []
        // fileList: [{name: 'food.jpeg', url: 'https://fuss10.elemecdn.com/3/63/4e7f3a15429bfda99bce42a18cdd1jpeg.jpeg?imageMogr2/thumbnail/360x360/format/webp/quality/100'}, {name: 'food2.jpeg', url: 'https://fuss10.elemecdn.com/3/63/4e7f3a15429bfda99bce42a18cdd1jpeg.jpeg?imageMogr2/thumbnail/360x360/format/webp/quality/100'}]
      }
    },
    methods: {
      handleRemove (file, fileList) {
        console.log(file, fileList)
      },
      handlePreview (file) {
        console.log(file)
      },
      handleBeforeUpload (file) {
        this.$message({
          message:  file.name + '正在上传'
        })
      },
      handleSuccess () {
        this.$message({
          message: '上传成功'
        })
      },
      handleError () {
        this.$message({
          type: 'error',
          message: '上传失败'
        })
      },
      handleExceed (files, fileList) {
        this.$message.warning(`当前限制选择 3 个文件，本次选择了 ${files.length} 个文件，共选择了 ${files.length + fileList.length} 个文件`)
      },
      beforeRemove (file, fileList) {
        return this.$confirm(`确定移除 ${file.name}？`)
      }
    }
  }
</script>
