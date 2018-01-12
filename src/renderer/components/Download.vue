<template>
  <div class="container">
    <el-input placeholder="请输入内容" v-model="input" class="input-with-select" style="visibility: hidden">
      <el-button slot="append" icon="el-icon-search"></el-button>
    </el-input> 
    <el-table :data="tableData" border style="width: 80%; margin-left: 10%">
      <el-table-column prop="name" label="文件名"></el-table-column>
      <el-table-column prop="size" label="文件大小"></el-table-column>
      <el-table-column prop="uploadTime" label="创建时间"></el-table-column>
      <el-table-column label="下载">
        <template slot-scope="scope">
        <el-button type="text" @click.native.prevent="downloadRow(scope.$index, scope.row.name, scope.row.address)" size="small">
          下载
        </el-button>
      </template>
      </el-table-column>
    </el-table>
  </div>
</template>
<style>
.container {
  margin-left: 250px;
}
.input-with-select {
  width: 30%;
  margin: 40px auto;
}
div.cell {
  text-align: center;
}
</style>
<script>
export default {
  name: "Download",
  created() {
    let self = this;
    this.$electron.ipcRenderer.on(
      "download-file-complete",
      function(event, name) {
        this.$message({
          type: "success",
          message: `文件 ${name} 下载成功`
        });
      }.bind(self)
    );
    this.$electron.ipcRenderer.on(
      "download-file-fail",
      function(event, errMsg) {
        this.$message({
          type: "error",
          message: `文件 $name 下载失败: ${errMsg}`
        });
      }.bind(self)
    );
    this.getData();
  },
  data() {
    return {
      input: "",
      // tableData: []
      tableData: [
        {
          uploadTime: "2016-05-02",
          name: "咩酱",
          size: 256,
          address: "https://www.miejiang.com"
        },
        {
          uploadTime: "2016-05-04",
          name: "咩酱",
          size: 256,
          address: "https://www.miejiang.com"
        },
        {
          uploadTime: "2016-05-01",
          name: "咩酱",
          size: 256,
          address: "https://www.miejiang.com"
        },
        {
          uploadTime: "2016-05-03",
          name: "咩酱",
          size: 256,
          address: "https://www.miejiang.com"
        }
      ]
    };
  },
  methods: {
    getData() {
      // Zumium 在get方法中添加get的url
      // 返回的格式为 data={'tableData': []}
      // 成功返回数据后，可以将上面定义的tableData的数据清空, 如tableData上的注释格式
      // this.$http.get("").then(res => {

      // this.$electron.ipcRenderer.sendSync('fetch-file-infos').then(res => {
      //   this.tableData = res.data.tableData; //数组类型，格式同上面tableData
      // });

      let filesObj = this.$electron.ipcRenderer.sendSync("fetch-file-infos");
      let r = [];
      for (let key in filesObj) {
        let f = filesObj[key];
        f.name = key;
        r.push(f);
      }

      this.tableData = r;
    },
    downloadRow(index, name, address) {
      console.log(index, name, address);
      // Zumium 在post方法中添加post的url
      // 如果下载成功，返回为 data={'return': true}, 可修改返回的变量名，对应在res.data.return中修改
      // this.$http.post("", params).then(res => {
      this.$electron.ipcRenderer.send("download-file", name);
    }
  }
};
</script>