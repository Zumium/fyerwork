<template>
  <div class="container">
    <el-input placeholder="请输入内容" v-model="input" class="input-with-select" style="visibility: hidden">
      <el-button slot="append" icon="el-icon-search"></el-button>
    </el-input>	
    <el-table :data="tableData" border style="width: 80%; margin-left: 10%">
      <el-table-column prop="date" label="日期"></el-table-column>
      <el-table-column prop="name" label="文件名"></el-table-column>
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
    name: 'Download',
    data () {
      return {
        input: '',
        tableData: [{
          date: '2016-05-02',
          name: '咩酱',
          address: 'https://www.miejiang.com'
        }, {
          date: '2016-05-04',
          name: '咩酱',
          address: 'https://www.miejiang.com'
        }, {
          date: '2016-05-01',
          name: '咩酱',
          address: 'https://www.miejiang.com'
        }, {
          date: '2016-05-03',
          name: '咩酱',
          address: 'https://www.miejiang.com'
        }]
      }
    },
    methods: {
      downloadRow (index, name, address) {
        console.log(index, name, address)
      }
    }
  }
</script>