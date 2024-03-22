<h1>
    <meta charset = "UTF-8">
    フォーム送信
</h1>
<form action="form2.php" method="post">
    <input type="text" name="mess">
    <input type="submit" value="送る">

</form>

<?php
if(isset($_POST['mess'])) {
    echo $_POST['mess'];
}
?>