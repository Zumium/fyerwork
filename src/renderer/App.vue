<template>
  <div id="app">
  	<m-nav></m-nav>
    <router-view></router-view>
  </div>
</template>

<script>
import Nav from "@/components/Nav";
export default {
  name: "fyerwork",
  components: {
    "m-nav": Nav
  }
};
</script>

<style>
/* CSS */
</style>
