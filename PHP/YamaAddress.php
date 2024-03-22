<h1>
    <meta charset = "UTF-8">
    山梨県の住所検索
</h1>
<form action="YamaAddress.php" method="post">
    <input type="text" name="mess">
    <input type="submit" value="検索">

</form>

<?php
if(isset($_POST['mess'])) {
    $addr = $_POST['mess'];
    echo "検索結果".'<br/>';
    
    $user = 'it15';
    $password = 'IT15';
    $dbname = 'sample';

    $mydb = mysqli_connect('localhost',$user,$password,$dbname);

    if(mysqli_connect_error()>0) {
        echo ('connect_error');
        exit();
    }

    mysqli_set_charset($mydb,"utf8");

    $sql = 'SELECT * FROM address WHERE id = '.$addr;  

    if ($res=mysqli_query($mydb,$sql)) {
        $row = mysqli_fetch_assoc($res);
        echo $row["pref"].$row["city"].$row["town"];
    }

    mysqli_close($mydb);
}
?>