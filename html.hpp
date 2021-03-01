
namespace scuweb
{
static const char * indexHtml = R"V0G0N(

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="utf-8">
    <meta http-equiv="content-security-policy" content="">
    <link rel="stylesheet" href="https://www.layuicdn.com/layui-v2.5.7/css/layui.css " type="text/css" media="all">
    <script src="https://www.layuicdn.com/auto/layui.js" v="layui" e="layui"></script>
    <style type="text/css">
        .container{
            width: 420px;
            height: 320px;
            min-height: 320px;
            max-height: 320px;
            position: absolute;
            top: 0;
            left: 0;
            bottom: 50px;
            right: 0;
            margin: auto;
            margin-button: 20px;
            padding: 50px;
            z-index: 130;
            border-radius: 8px;
            background-color: #fff;
            box-shadow: 0 3px 3px rgba(100, 0, 0, .5);
            font-size: 16px;
        }
        .close{
            background-color: white;
            border: none;
            font-size: 18px;
            margin-left: 410px;
            margin-top: -10px;
        }

        .layui-input{
            border-radius: 5px;
            width: 300px;
            height: 40px;
            font-size: 15px;
        }
        .layui-form-item{
            margin-left: -20px;
        }
        .layui-form-label {
            float: left;
            display: block;
            padding: 9px 15px;
            width: 80px;
            line-height: 20px;
            text-align: right;
            margin-top: 10px;
        }
        .layui-form-switch {
            position: relative;
            height: 22px;
            line-height: 22px;
            min-width: 35px;
            padding: 0 5px;
            margin-top: 18px;
            cursor: pointer;
            background-color: #fff;
            -webkit-transition: .1s linear;
            transition: .1s linear;
        }
        #logoid{
            margin-top: -16px;
            padding-left:150px;
            padding-bottom: 15px;
        }
        .layui-btn{
            margin-left: -50px;
            margin-top: 50px;
            border-radius: 5px;
            width: 350px;
            height: 40px;
            font-size: 15px;
        }
        .verity{
            width: 120px;
        }
        .font-set{
            font-size: 13px;
            text-decoration: none;
            margin-left: 120px;
        }
        a:hover{
            text-decoration: underline;
        }
    </style>
</head>
<body>
<form class="layui-form" action="" method="post">
    <div class="container">
        <div class="layui-form-item">
            <label class="layui-form-label">用户名</label>
            <div class="layui-input-block">
                <input type="text" name="username" required  lay-verify="required" placeholder="请输入用户名" autocomplete="off" class="layui-input">
            </div>
        </div>
        <div class="layui-form-item">
            <label class="layui-form-label">密 &nbsp;&nbsp;码</label>
            <div class="layui-input-inline">
                <input type="password" name="password" required lay-verify="required" placeholder="请输入密码" autocomplete="off" class="layui-input">
            </div>
        </div>
        <div class="layui-form-item">
            <div class="layui-input-block">
                <button class="layui-btn" lay-submit="" lay-filter="formLogin">登陆</button>
            </div>
        </div>
    </div>
</form>
</body>
<script type="text/javascript">
    layui.use(['form', 'layer'], function(){
        var form = layui.form
            ,layer = layui.layer
        ,$ = layui.$;
        
        form.on('submit(formLogin)', function(data){
            $.ajax({
                url: '/login',
                type: 'POST',
                data: JSON.stringify(data.field),
                success: function(data){
                    let res = JSON.parse(data);
                    if(res.code === 0 && res.msg === 'ok'){
                    layer.msg('登录成功',{
                            icon: 1,
                            time: 2000
                    },function(){
                            window.location.href = 'net.html';
                    })
                    }else{
                        layer.msg('用户名或密码错误',{
                            icon: 2,
                            time: 2000,
                            shift: 6            
                        },function(){
                            window.location.reload();           
                        })      
                    }
                },
                error: function(){
                    layer.msg('服务器连接异常',{
                        icon: 2,
                        time: 2000,
                        shift: 6
                    },function(){
                        window.location.reload();
                    })
                }
            })
            return false;
        });
    });
</script>
</html>

)V0G0N";

static const char * netHtml = R"V0G0N(

<!DOCTYPE html>
<html>
<head>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1, maximum-scale=1">
    <title>网络设置</title>
    <link rel="stylesheet" href="https://www.layuicdn.com/layui-v2.5.7/css/layui.css " type="text/css" media="all">
    <script src="https://www.layuicdn.com/auto/layui.js" v="layui" e="layui"></script>
</head>
<body class="layui-layout-body">
<div class="layui-layout layui-layout-admin">
    <div class="layui-header">
        <div class="layui-logo">设备配置</div>

        <ul class="layui-nav layui-layout-left">
            <li class="layui-nav-item layui-this"><a href="net.html">网络设置</a></li>
            <li class="layui-nav-item"><a href="channel1.html">通道设置</a></li>
        </ul>
    </div>

    <div class="layui-side layui-bg-black">
        <div class="layui-side-scroll">
            <ul class="layui-nav layui-nav-tree">
                <li class="layui-nav-item"><a href="net.html">基础设置</a></li>
                <li class="layui-nav-item"><a href="connect.html">平台连接</a></li>
            </ul>
        </div>
    </div>

    <div class="layui-body">
        <fieldset class="layui-elem-field">
            <div class="layui-field-box">
                <form class="layui-form" action="">
                    <hr class="layui-bg-gray">
                    <div class="layui-form-item">
                        <div class="layui-inline">
                            <label class="layui-form-label">设备名称：</label>
                            <div class="layui-input-inline">
                                <input type="text" name="deviceName" autocomplete="off" class="layui-input">
                            </div>
                        </div>
                        <div class="layui-inline">
                            <p class="layui-inline">型号： HTZH AI01</p></label>
                        </div>
                    </div>
                    <div class="layui-form-item">
                        <div class="layui-inline">
                            <label class="layui-form-label">安装位置：</label>
                            <div class="layui-input-inline">
                                <input type="text" name="devicePlace" autocomplete="off" class="layui-input">
                            </div>
                        </div>
                        <div class="layui-inline">
                            <p class="layui-inline">SN： 1110 2395 b377 3304 361</p>
                        </div>
                    </div>
                    <hr class="layui-bg-gray">

                    <p>LAN-1</p>
                    <hr class="layui-bg-gray">
                    <div class="layui-form-item">
                        <label class="layui-form-label" id="sex">设置方式：</label>
                        <input  type="radio" name="LAN-1_mode" value="auto" title="自动获取"/>
                        <input  type="radio" name="LAN-1_mode" value="manual" title="手动设置" />
                    </div>
                    <div id="LAN-1_input">
                        <div class="layui-form-item">
                            <div class="layui-inline">
                                <label class="layui-form-label">ip地址：</label>
                                <div class="layui-input-inline">
                                    <input type="text" name="LAN-1_ip" autocomplete="off" class="layui-input">
                                </div>
                            </div>
                            <div class="layui-inline">
                                <label class="layui-form-label">端口：</label>
                                <div class="layui-input-inline">
                                    <input type="text" name="LAN-1_port" autocomplete="off" class="layui-input">
                                </div>
                            </div>
                        </div>

                        <div class="layui-form-item">
                            <div class="layui-inline">
                                <label class="layui-form-label">子网掩码：</label>
                                <div class="layui-input-inline">
                                    <input type="text" name="LAN-1_mask" autocomplete="off" class="layui-input">
                                </div>
                            </div>
                            <div class="layui-inline">
                                <label class="layui-form-label">网关：</label>
                                <div class="layui-input-inline">
                                    <input type="text" name="LAN-1_gateway" autocomplete="off" class="layui-input">
                                </div>
                            </div>
                        </div>

                        <div class="layui-form-item">
                            <div class="layui-inline">
                                <label class="layui-form-label">首选DNS：</label>
                                <div class="layui-input-inline">
                                    <input type="text" name="LAN-1_firstDNS" autocomplete="off" class="layui-input">
                                </div>
                            </div>
                            <div class="layui-inline">
                                <label class="layui-form-label">备选DNS：</label>
                                <div class="layui-input-inline">
                                    <input type="text" name="LAN-1_secondDNS" autocomplete="off" class="layui-input">
                                </div>
                            </div>
                        </div>
                    </div>

                    <hr class="layui-bg-gray">

                    <p>LAN-2</p>
                    <hr class="layui-bg-gray">

                    <div class="layui-form-item">
                        <div class="layui-inline">
                            <label class="layui-form-label">设置方式：</label>
                            <div class="layui-input-block">
                                <input type="radio" name="LAN-2_mode" value="auto" title="自动获取" οnclick="check2()">
                                <input type="radio" name="LAN-2_mode" value="manual" title="手动设置">
                            </div>
                        </div>
                    </div>
                    <div id="LAN-2_input">
                        <div class="layui-form-item">
                            <div class="layui-inline">
                                <label class="layui-form-label">ip地址：</label>
                                <div class="layui-input-inline">
                                    <input type="text" name="LAN-2_ip" autocomplete="off" class="layui-input">
                                </div>
                            </div>
                            <div class="layui-inline">
                                <label class="layui-form-label">端口：</label>
                                <div class="layui-input-inline">
                                    <input type="text" name="LAN-2_port" autocomplete="off" class="layui-input">
                                </div>
                            </div>
                        </div>

                        <div class="layui-form-item">
                            <div class="layui-inline">
                                <label class="layui-form-label">子网掩码：</label>
                                <div class="layui-input-inline">
                                    <input type="text" name="LAN-2_mask" autocomplete="off" class="layui-input">
                                </div>
                            </div>
                            <div class="layui-inline">
                                <label class="layui-form-label">网关：</label>
                                <div class="layui-input-inline">
                                    <input type="text" name="LAN-2_gateway" autocomplete="off" class="layui-input">
                                </div>
                            </div>
                        </div>

                        <div class="layui-form-item">
                            <div class="layui-inline">
                                <label class="layui-form-label">首选DNS：</label>
                                <div class="layui-input-inline">
                                    <input type="text" name="LAN-2_firstDNS" autocomplete="off" class="layui-input">
                                </div>
                            </div>
                            <div class="layui-inline">
                                <label class="layui-form-label">备选DNS：</label>
                                <div class="layui-input-inline">
                                    <input type="text" name="LAN-2_secondDNS" autocomplete="off" class="layui-input">
                                </div>
                            </div>
                        </div>
                    </div>
 
                    <hr class="layui-bg-gray">

                    <div class="layui-form-item">
                        <button class="layui-btn" type="submit" lay-submit="" lay-filter="formNet">提交</button>
                        <button type="reset" class="layui-btn layui-btn-primary">重置</button>
                    </div>
                </form>
            </div>
        </fieldset>
    </div>
</div>
</body>
<script type="text/javascript">
layui.use(['form','layer'], function(){
    var form = layui.form
    ,layer = layui.layer
    ,$ = layui.$;

    form.render();
    //监听提交
    form.on('submit(formNet)', function(data){
        $.ajax({
            url: '/net',
            type: 'POST',
            data: JSON.stringify(data.field),
            success: function(data){
                let res = JSON.parse(data);
                if(res.code === 1 && res.msg === 'ok'){
                    layer.msg('设置成功',{
                        icon: 1,
                        time: 2000
                    })
                }else{
                    layer.msg('设置失败',{
                        icon: 2,
                        time: 2000,
                        shift: 6
                    })
                }
            },
            error: function(){
                layer.msg('服务器连接异常',{
                    icon: 2,
                    time: 2000,
                    shift: 6
                },function(){
                    window.location.reload();
                })
            }
        })
        return false;
    });
});
</script>
</html>

)V0G0N";

static const char * connectHtml = R"VOGON(

<!DOCTYPE html>
<html>
<head>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1, maximum-scale=1">
    <title>网络设置</title>
    <link rel="stylesheet" href="https://www.layuicdn.com/layui-v2.5.7/css/layui.css " type="text/css" media="all">
    <script src="https://www.layuicdn.com/auto/layui.js" v="layui" e="layui"></script>
</head>
<body class="layui-layout-body">
<div class="layui-layout layui-layout-admin">
    <div class="layui-header">
        <div class="layui-logo">设备配置</div>

        <ul class="layui-nav layui-layout-left">
            <li class="layui-nav-item layui-this"><a href="net.html">网络设置</a></li>
            <li class="layui-nav-item"><a href="channel1.html">通道设置</a></li>
        </ul>
    </div>

    <div class="layui-side layui-bg-black">
        <div class="layui-side-scroll">
            <ul class="layui-nav layui-nav-tree">
                <li class="layui-nav-item"><a href="net.html">基础设置</a></li>
                <li class="layui-nav-item"><a href="connect.html">平台连接</a></li>
            </ul>
        </div>
    </div>

    <div class="layui-body">
        <fieldset class="layui-elem-field layui-col-lg5">
            <div class="layui-field-box">
                <form class="layui-form" action="">
                    <hr class="layui-bg-gray">
                    <p id="text" class="layui-text">平台服务器配置</p>
                    <div class="layui-form-item">
                        <div class="layui-inline">
                            <label class="layui-form-label">IP地址：</label>
                            <div class="layui-input-inline">
                                <input type="text" name="ip" autocomplete="off" class="layui-input">
                            </div>
                        </div>
                    </div>
                    <div class="layui-form-item">
                        <div class="layui-inline">
                            <label class="layui-form-label">端口：</label>
                            <div class="layui-input-inline">
                                <input type="text" name="port" autocomplete="off" class="layui-input">
                            </div>
                        </div>
                    </div>
                    <div id="btnAct">
                        <button type="submit" class="layui-btn layui-btn-normal layui-btn-radius" lay-submit="" lay-filter="formConnect">设备激活</button>
                    </div>
                </form>
            </div>
        </fieldset>
    </div>
</div>
</body>
<script type="text/javascript">
layui.use(['form','layer'], function(){
    var form = layui.form
    ,layer = layui.layer
    ,$ = layui.$;

    form.render();
    //监听提交
    form.on('submit(formConnect)', function(data){
        $.ajax({
            url: '/connect',
            type: 'POST',
            data: JSON.stringify(data.field),
            success: function(data){
                let res = JSON.parse(data);
                if(res.code === 1 && res.msg === 'ok'){
                    layer.msg('设置成功',{
                        icon: 1,
                        time: 2000
                    })
                }else{
                    layer.msg('设置失败',{
                        icon: 2,
                        time: 2000,
                        shift: 6
                    })
                }
            },
            error: function(){
                layer.msg('服务器连接异常',{
                    icon: 2,
                    time: 2000,
                    shift: 6
                },function(){
                    window.location.reload();
                })
            }
        })
        return false;
    });
});
</script>
</html>
)VOGON";

static const char * channel1Html = R"VOGON(

<!DOCTYPE html>
<html>
<head>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1, maximum-scale=1">
    <title>通道一设置</title>
    <link rel="stylesheet" href="https://www.layuicdn.com/layui-v2.5.7/css/layui.css " type="text/css" media="all">
    <script src="https://www.layuicdn.com/auto/layui.js" v="layui" e="layui"></script>
    <style type="text/css">
    #channelNum{
        padding-left: 40px;
    }
    #wholeBody{
        padding: 15px;
    }
    #channelName{
        padding-left: 25px;
    }
    #buttonOpen{
        float: right;
        padding: 20px;
    }
    </style>

</head>
<body class="layui-layout-body">
<div class="layui-layout layui-layout-admin">
    <div class="layui-header">
        <div class="layui-logo">设备配置</div>

        <ul class="layui-nav layui-layout-left">
            <li class="layui-nav-item"><a href="net.html">网络设置</a></li>
            <li class="layui-nav-item layui-this"><a href="channel1.html">通道设置</a></li>
        </ul>
    </div>

    <div class="layui-side layui-bg-black">
        <div class="layui-side-scroll">
            <ul class="layui-nav layui-nav-tree">
                <li class="layui-nav-item"><a href="channel1.html">通道一</a></li>
                <li class="layui-nav-item"><a href="channel2.html">通道二</a></li>
                <li class="layui-nav-item"><a href="channel3.html">通道三</a></li>
                <li class="layui-nav-item"><a href="channel4.html">通道四</a></li>
                <li class="layui-nav-item"><a href="channel5.html">通道五</a></li>
            </ul>
        </div>
    </div>

    <div class="layui-body">
        <div id="wholeBody">
            <form class="layui-form" action="">
                <fieldset class="layui-elem-field layui-col-lg7 layui-col-lg-offset1">
                    <div class="layui-field-box">
                        <div class="layui-form-item">
                            <p class="layui-inline" id="channelNum">通道号： 通道一</p>
                            <div class="layui-inline layui-col-lg-offset2" id="channel-1_Name">
                                <label class="layui-form-label">别名：</label>
                                <div class="layui-input-inline">
                                    <input type="text" name="channel-1_Name" autocomplete="off" class="layui-input">
                                </div>
                            </div>
                        </div>
                        <div class="layui-form-item">
                            <div class="layui-inline">
                                <label class="layui-form-label">通道状态：</label>
                                <div class="layui-input-block">
                                    <input type="checkbox" checked="" name="channel-1_Status" lay-skin="switch" lay-filter="switchTest" lay-text="ON|OFF">
                                </div>
                            </div>

                            <div class="layui-inline layui-col-lg-offset2">
                                <label class="layui-form-label">监控类型:</label>
                                <div class="layui-input-block">
                                    <select name="channel-1_deviceType" lay-filter="channel-1_deviceType">
                                        <option value=""></option>
                                        <option value="枪机" selected="">枪机</option>
                                        <option value="球机" >球机</option>
                                    </select>
                                </div>
                            </div>
                        </div>

                        <div class="layui-form-item">
                            <div class="layui-inline">
                                <label class="layui-form-label">监控地点：</label>
                                <div class="layui-input-block">
                                    <input name="channel-1_monitorPlace" type="text" class="layui-input" placeholder="请输入设备安装地点">
                                </div>
                            </div>

                            <div class="layui-inline">
                                <label class="layui-form-label">协议类型：</label>
                                <div class="layui-input-block">
                                    <input name="channel-1_protocol" type="text" class="layui-input" placeholder="请输入设备协议">
                                </div>
                            </div>
                        </div>

                        <div class="layui-form-item">
                            <div class="layui-inline">
                                <label class="layui-form-label">IP地址：</label>
                                <div class="layui-input-block">
                                    <input name="channel-1_deviceIp" type="text" class="layui-input" placeholder="请输入设备IP地址">
                                </div>
                            </div>

                            <div class="layui-inline">
                                <label class="layui-form-label">端口：</label>
                                <div class="layui-input-block">
                                    <input name="channel-1_devicePort" type="text" class="layui-input" placeholder="请输入设备端口号">
                                </div>
                            </div>
                        </div>

                        <div class="layui-form-item layui-form-text">
                            <label class="layui-form-label">备注：</label>
                            <div class="layui-input-block">
                                <textarea placeholder="请输入备注说明" class="layui-textarea"></textarea>
                            </div>
                        </div>
                    </div>
                    <div class="layui-form-item" id="buttonOpen">
                        <button class="layui-btn" type="submit" lay-submit="" lay-filter="formChannel1">确定</button>
                    </div>
                </fieldset>
            </form>
        </div>
    </div>
</div>
</body>
<script type="text/javascript">
layui.use(['form','layer'], function(){
    var form = layui.form
        ,layer = layui.layer
        ,$ = layui.$;
    form.render();
    form.on('submit(formChannel1)', function(data){
        $.ajax({
            url: '/channel1',
            type: 'POST',
            data: JSON.stringify(data.field),
            success: function(data){
                let res = JSON.parse(data);
                if(res.code === 1 && res.msg === 'ok'){
                    layer.msg('设置成功',{
                        icon: 1,
                        time: 2000
                    })
                }else{
                    layer.msg('设置失败',{
                        icon: 2,
                        time: 2000,
                        shift: 6
                    })
                }
            },
            error: function(){
                layer.msg('服务器连接异常',{
                    icon: 2,
                    time: 2000,
                    shift: 6
                },function(){
                    window.location.reload();
                })
            }
        })
        return false;
    });
});
</script>
</html>

)VOGON";

static const char * channel2Html = R"VOGON(
<!DOCTYPE html>
<html>
<head>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1, maximum-scale=1">
    <title>通道二设置</title>
    <link rel="stylesheet" href="https://www.layuicdn.com/layui-v2.5.7/css/layui.css " type="text/css" media="all">
    <script src="https://www.layuicdn.com/auto/layui.js" v="layui" e="layui"></script>
    <style type="text/css">
    #channelNum{
        padding-left: 40px;
    }
    #wholeBody{
        padding: 15px;
    }
    #channelName{
        padding-left: 25px;
    }
    #buttonOpen{
        float: right;
        padding: 20px;
    }
    </style>

</head>
<body class="layui-layout-body">
<div class="layui-layout layui-layout-admin">
    <div class="layui-header">
        <div class="layui-logo">设备配置</div>

        <ul class="layui-nav layui-layout-left">
            <li class="layui-nav-item"><a href="net.html">网络设置</a></li>
            <li class="layui-nav-item layui-this"><a href="channel2.html">通道设置</a></li>
        </ul>
    </div>

    <div class="layui-side layui-bg-black">
        <div class="layui-side-scroll">
            <ul class="layui-nav layui-nav-tree">
                <li class="layui-nav-item"><a href="channel1.html">通道一</a></li>
                <li class="layui-nav-item"><a href="channel2.html">通道二</a></li>
                <li class="layui-nav-item"><a href="channel3.html">通道三</a></li>
                <li class="layui-nav-item"><a href="channel4.html">通道四</a></li>
                <li class="layui-nav-item"><a href="channel5.html">通道五</a></li>
            </ul>
        </div>
    </div>

    <div class="layui-body">
        <div id="wholeBody">
            <form class="layui-form" action="">
                <fieldset class="layui-elem-field layui-col-lg7 layui-col-lg-offset1">
                    <div class="layui-field-box">
                        <div class="layui-form-item">
                            <p class="layui-inline" id="channelNum">通道号： 通道二</p>
                            <div class="layui-inline layui-col-lg-offset2" id="channel-2_Name">
                                <label class="layui-form-label">别名：</label>
                                <div class="layui-input-inline">
                                    <input type="text" name="channel-2_Name" autocomplete="off" class="layui-input">
                                </div>
                            </div>
                        </div>
                        <div class="layui-form-item">
                            <div class="layui-inline">
                                <label class="layui-form-label">通道状态：</label>
                                <div class="layui-input-block">
                                    <input type="checkbox" checked="" name="channel-2_Status" lay-skin="switch" lay-filter="switchTest" lay-text="ON|OFF">
                                </div>
                            </div>

                            <div class="layui-inline layui-col-lg-offset2">
                                <label class="layui-form-label">监控类型:</label>
                                <div class="layui-input-block">
                                    <select name="channel-2_deviceType" lay-filter="channel-2_deviceType">
                                        <option value=""></option>
                                        <option value="枪机" selected="">枪机</option>
                                        <option value="球机" >球机</option>
                                    </select>
                                </div>
                            </div>
                        </div>

                        <div class="layui-form-item">
                            <div class="layui-inline">
                                <label class="layui-form-label">监控地点：</label>
                                <div class="layui-input-block">
                                    <input name="channel-2_monitorPlace" type="text" class="layui-input" placeholder="请输入设备安装地点">
                                </div>
                            </div>

                            <div class="layui-inline">
                                <label class="layui-form-label">协议类型：</label>
                                <div class="layui-input-block">
                                    <input name="channel-2_protocol" type="text" class="layui-input" placeholder="请输入设备协议">
                                </div>
                            </div>
                        </div>

                        <div class="layui-form-item">
                            <div class="layui-inline">
                                <label class="layui-form-label">IP地址：</label>
                                <div class="layui-input-block">
                                    <input name="channel-2_deviceIp" type="text" class="layui-input" placeholder="请输入设备IP地址">
                                </div>
                            </div>

                            <div class="layui-inline">
                                <label class="layui-form-label">端口：</label>
                                <div class="layui-input-block">
                                    <input name="channel-2_devicePort" type="text" class="layui-input" placeholder="请输入设备端口号">
                                </div>
                            </div>
                        </div>

                        <div class="layui-form-item layui-form-text">
                            <label class="layui-form-label">备注：</label>
                            <div class="layui-input-block">
                                <textarea placeholder="请输入备注说明" class="layui-textarea"></textarea>
                            </div>
                        </div>
                    </div>
                    <div class="layui-form-item" id="buttonOpen">
                        <button class="layui-btn" type="submit" lay-submit="" lay-filter="formChannel2">确定</button>
                    </div>
                </fieldset>
            </form>
        </div>
    </div>
</div>
</body>
<script type="text/javascript">
layui.use(['form','layer'], function(){
    var form = layui.form
        ,layer = layui.layer
        ,$ = layui.$;
    form.render();
    form.on('submit(formChannel2)', function(data){
        $.ajax({
            url: '/channel2',
            type: 'POST',
            data: JSON.stringify(data.field),
            success: function(data){
                let res = JSON.parse(data);
                if(res.code === 1 && res.msg === 'ok'){
                    layer.msg('设置成功',{
                        icon: 1,
                        time: 2000
                    })
                }else{
                    layer.msg('设置失败',{
                        icon: 2,
                        time: 2000,
                        shift: 6
                    })
                }
            },
            error: function(){
                layer.msg('服务器连接异常',{
                    icon: 2,
                    time: 2000,
                    shift: 6
                },function(){
                    window.location.reload();
                })
            }
        })
        return false;
    });
});
</script>
</html>
)VOGON";

static const char * channel3Html = R"VOGON(
<!DOCTYPE html>
<html>
<head>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1, maximum-scale=1">
    <title>通道三设置</title>
    <link rel="stylesheet" href="https://www.layuicdn.com/layui-v2.5.7/css/layui.css " type="text/css" media="all">
    <script src="https://www.layuicdn.com/auto/layui.js" v="layui" e="layui"></script>
    <style type="text/css">
    #channelNum{
        padding-left: 40px;
    }
    #wholeBody{
        padding: 15px;
    }
    #channelName{
        padding-left: 25px;
    }
    #buttonOpen{
        float: right;
        padding: 20px;
    }
    </style>

</head>
<body class="layui-layout-body">
<div class="layui-layout layui-layout-admin">
    <div class="layui-header">
        <div class="layui-logo">设备配置</div>

        <ul class="layui-nav layui-layout-left">
            <li class="layui-nav-item"><a href="net.html">网络设置</a></li>
            <li class="layui-nav-item layui-this"><a href="channel3.html">通道设置</a></li>
        </ul>
    </div>

    <div class="layui-side layui-bg-black">
        <div class="layui-side-scroll">
            <ul class="layui-nav layui-nav-tree">
                <li class="layui-nav-item"><a href="channel1.html">通道一</a></li>
                <li class="layui-nav-item"><a href="channel2.html">通道二</a></li>
                <li class="layui-nav-item"><a href="channel3.html">通道三</a></li>
                <li class="layui-nav-item"><a href="channel4.html">通道四</a></li>
                <li class="layui-nav-item"><a href="channel5.html">通道五</a></li>
            </ul>
        </div>
    </div>

    <div class="layui-body">
        <div id="wholeBody">
            <form class="layui-form" action="">
                <fieldset class="layui-elem-field layui-col-lg7 layui-col-lg-offset1">
                    <div class="layui-field-box">
                        <div class="layui-form-item">
                            <p class="layui-inline" id="channelNum">通道号： 通道三</p>
                            <div class="layui-inline layui-col-lg-offset2" id="channel-3_Name">
                                <label class="layui-form-label">别名：</label>
                                <div class="layui-input-inline">
                                    <input type="text" name="channel-3_Name" autocomplete="off" class="layui-input">
                                </div>
                            </div>
                        </div>
                        <div class="layui-form-item">
                            <div class="layui-inline">
                                <label class="layui-form-label">通道状态：</label>
                                <div class="layui-input-block">
                                    <input type="checkbox" checked="" name="channel-3_Status" lay-skin="switch" lay-filter="switchTest" lay-text="ON|OFF">
                                </div>
                            </div>

                            <div class="layui-inline layui-col-lg-offset2">
                                <label class="layui-form-label">监控类型:</label>
                                <div class="layui-input-block">
                                    <select name="channel-3_deviceType" lay-filter="channel-3_deviceType">
                                        <option value=""></option>
                                        <option value="枪机" selected="">枪机</option>
                                        <option value="球机" >球机</option>
                                    </select>
                                </div>
                            </div>
                        </div>

                        <div class="layui-form-item">
                            <div class="layui-inline">
                                <label class="layui-form-label">监控地点：</label>
                                <div class="layui-input-block">
                                    <input name="channel-3_monitorPlace" type="text" class="layui-input" placeholder="请输入设备安装地点">
                                </div>
                            </div>

                            <div class="layui-inline">
                                <label class="layui-form-label">协议类型：</label>
                                <div class="layui-input-block">
                                    <input name="channel-3_protocol" type="text" class="layui-input" placeholder="请输入设备协议">
                                </div>
                            </div>
                        </div>

                        <div class="layui-form-item">
                            <div class="layui-inline">
                                <label class="layui-form-label">IP地址：</label>
                                <div class="layui-input-block">
                                    <input name="channel-3_deviceIp" type="text" class="layui-input" placeholder="请输入设备IP地址">
                                </div>
                            </div>

                            <div class="layui-inline">
                                <label class="layui-form-label">端口：</label>
                                <div class="layui-input-block">
                                    <input name="channel-3_devicePort" type="text" class="layui-input" placeholder="请输入设备端口号">
                                </div>
                            </div>
                        </div>

                        <div class="layui-form-item layui-form-text">
                            <label class="layui-form-label">备注：</label>
                            <div class="layui-input-block">
                                <textarea placeholder="请输入备注说明" class="layui-textarea"></textarea>
                            </div>
                        </div>
                    </div>
                    <div class="layui-form-item" id="buttonOpen">
                        <button class="layui-btn" type="submit" lay-submit="" lay-filter="formChannel3">确定</button>
                    </div>
                </fieldset>
            </form>
        </div>
    </div>
</div>
</body>
<script type="text/javascript">
layui.use(['form','layer'], function(){
    var form = layui.form
        ,layer = layui.layer
        ,$ = layui.$;
    form.render();
    form.on('submit(formChannel3)', function(data){
        $.ajax({
            url: '/channel3',
            type: 'POST',
            data: JSON.stringify(data.field),
            success: function(data){
                let res = JSON.parse(data);
                if(res.code === 1 && res.msg === 'ok'){
                    layer.msg('设置成功',{
                        icon: 1,
                        time: 2000
                    })
                }else{
                    layer.msg('设置失败',{
                        icon: 2,
                        time: 2000,
                        shift: 6
                    })
                }
            },
            error: function(){
                layer.msg('服务器连接异常',{
                    icon: 2,
                    time: 2000,
                    shift: 6
                },function(){
                    window.location.reload();
                })
            }
        })
        return false;
    });
});
</script>
</html>
)VOGON";
static const char * channel4Html = R"VOGON(
<!DOCTYPE html>
<html>
<head>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1, maximum-scale=1">
    <title>通道四设置</title>
    <link rel="stylesheet" href="https://www.layuicdn.com/layui-v2.5.7/css/layui.css " type="text/css" media="all">
    <script src="https://www.layuicdn.com/auto/layui.js" v="layui" e="layui"></script>
    <style type="text/css">
    #channelNum{
        padding-left: 40px;
    }
    #wholeBody{
        padding: 15px;
    }
    #channelName{
        padding-left: 25px;
    }
    #buttonOpen{
        float: right;
        padding: 20px;
    }
    </style>

</head>
<body class="layui-layout-body">
<div class="layui-layout layui-layout-admin">
    <div class="layui-header">
        <div class="layui-logo">设备配置</div>

        <ul class="layui-nav layui-layout-left">
            <li class="layui-nav-item"><a href="net.html">网络设置</a></li>
            <li class="layui-nav-item layui-this"><a href="channel4.html">通道设置</a></li>
        </ul>
    </div>

    <div class="layui-side layui-bg-black">
        <div class="layui-side-scroll">
            <ul class="layui-nav layui-nav-tree">
                <li class="layui-nav-item"><a href="channel1.html">通道一</a></li>
                <li class="layui-nav-item"><a href="channel2.html">通道二</a></li>
                <li class="layui-nav-item"><a href="channel3.html">通道三</a></li>
                <li class="layui-nav-item"><a href="channel4.html">通道四</a></li>
                <li class="layui-nav-item"><a href="channel5.html">通道五</a></li>
            </ul>
        </div>
    </div>

    <div class="layui-body">
        <div id="wholeBody">
            <form class="layui-form" action="">
                <fieldset class="layui-elem-field layui-col-lg7 layui-col-lg-offset1">
                    <div class="layui-field-box">
                        <div class="layui-form-item">
                            <p class="layui-inline" id="channelNum">通道号： 通道四</p>
                            <div class="layui-inline layui-col-lg-offset2" id="channel-4_Name">
                                <label class="layui-form-label">别名：</label>
                                <div class="layui-input-inline">
                                    <input type="text" name="channel-4_Name" autocomplete="off" class="layui-input">
                                </div>
                            </div>
                        </div>
                        <div class="layui-form-item">
                            <div class="layui-inline">
                                <label class="layui-form-label">通道状态：</label>
                                <div class="layui-input-block">
                                    <input type="checkbox" checked="" name="channel-4_Status" lay-skin="switch" lay-filter="switchTest" lay-text="ON|OFF">
                                </div>
                            </div>

                            <div class="layui-inline layui-col-lg-offset2">
                                <label class="layui-form-label">监控类型:</label>
                                <div class="layui-input-block">
                                    <select name="channel-4_deviceType" lay-filter="channel-4_deviceType">
                                        <option value=""></option>
                                        <option value="枪机" selected="">枪机</option>
                                        <option value="球机" >球机</option>
                                    </select>
                                </div>
                            </div>
                        </div>

                        <div class="layui-form-item">
                            <div class="layui-inline">
                                <label class="layui-form-label">监控地点：</label>
                                <div class="layui-input-block">
                                    <input name="channel-4_monitorPlace" type="text" class="layui-input" placeholder="请输入设备安装地点">
                                </div>
                            </div>

                            <div class="layui-inline">
                                <label class="layui-form-label">协议类型：</label>
                                <div class="layui-input-block">
                                    <input name="channel-4_protocol" type="text" class="layui-input" placeholder="请输入设备协议">
                                </div>
                            </div>
                        </div>

                        <div class="layui-form-item">
                            <div class="layui-inline">
                                <label class="layui-form-label">IP地址：</label>
                                <div class="layui-input-block">
                                    <input name="channel-4_deviceIp" type="text" class="layui-input" placeholder="请输入设备IP地址">
                                </div>
                            </div>

                            <div class="layui-inline">
                                <label class="layui-form-label">端口：</label>
                                <div class="layui-input-block">
                                    <input name="channel-4_devicePort" type="text" class="layui-input" placeholder="请输入设备端口号">
                                </div>
                            </div>
                        </div>

                        <div class="layui-form-item layui-form-text">
                            <label class="layui-form-label">备注：</label>
                            <div class="layui-input-block">
                                <textarea placeholder="请输入备注说明" class="layui-textarea"></textarea>
                            </div>
                        </div>
                    </div>
                    <div class="layui-form-item" id="buttonOpen">
                        <button class="layui-btn" type="submit" lay-submit="" lay-filter="formChannel4">确定</button>
                    </div>
                </fieldset>
            </form>
        </div>
    </div>
</div>
</body>
<script type="text/javascript">
layui.use(['form','layer'], function(){
    var form = layui.form
        ,layer = layui.layer
        ,$ = layui.$;
    form.render();
    form.on('submit(formChannel4)', function(data){
        $.ajax({
            url: '/channel4',
            type: 'POST',
            data: JSON.stringify(data.field),
            success: function(data){
                let res = JSON.parse(data);
                if(res.code === 1 && res.msg === 'ok'){
                    layer.msg('设置成功',{
                        icon: 1,
                        time: 2000
                    })
                }else{
                    layer.msg('设置失败',{
                        icon: 2,
                        time: 2000,
                        shift: 6
                    })
                }
            },
            error: function(){
                layer.msg('服务器连接异常',{
                    icon: 2,
                    time: 2000,
                    shift: 6
                },function(){
                    window.location.reload();
                })
            }
        })
        return false;
    });
});
</script>
</html>
)VOGON";
static const char * channel5Html = R"VOGON(
<!DOCTYPE html>
<html>
<head>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1, maximum-scale=1">
    <title>通道五设置</title>
    <link rel="stylesheet" href="https://www.layuicdn.com/layui-v2.5.7/css/layui.css " type="text/css" media="all">
    <script src="https://www.layuicdn.com/auto/layui.js" v="layui" e="layui"></script>
    <style type="text/css">
    #channelNum{
        padding-left: 40px;
    }
    #wholeBody{
        padding: 15px;
    }
    #channelName{
        padding-left: 25px;
    }
    #buttonOpen{
        float: right;
        padding: 20px;
    }
    </style>

</head>
<body class="layui-layout-body">
<div class="layui-layout layui-layout-admin">
    <div class="layui-header">
        <div class="layui-logo">设备配置</div>

        <ul class="layui-nav layui-layout-left">
            <li class="layui-nav-item"><a href="net.html">网络设置</a></li>
            <li class="layui-nav-item layui-this"><a href="channel5.html">通道设置</a></li>
        </ul>
    </div>

    <div class="layui-side layui-bg-black">
        <div class="layui-side-scroll">
            <ul class="layui-nav layui-nav-tree">
                <li class="layui-nav-item"><a href="channel1.html">通道一</a></li>
                <li class="layui-nav-item"><a href="channel2.html">通道二</a></li>
                <li class="layui-nav-item"><a href="channel3.html">通道三</a></li>
                <li class="layui-nav-item"><a href="channel4.html">通道四</a></li>
                <li class="layui-nav-item"><a href="channel5.html">通道五</a></li>
            </ul>
        </div>
    </div>

    <div class="layui-body">
        <div id="wholeBody">
            <form class="layui-form" action="">
                <fieldset class="layui-elem-field layui-col-lg7 layui-col-lg-offset1">
                    <div class="layui-field-box">
                        <div class="layui-form-item">
                            <p class="layui-inline" id="channelNum">通道号： 通道五</p>
                            <div class="layui-inline layui-col-lg-offset2" id="channel-5_Name">
                                <label class="layui-form-label">别名：</label>
                                <div class="layui-input-inline">
                                    <input type="text" name="channel-5_Name" autocomplete="off" class="layui-input">
                                </div>
                            </div>
                        </div>
                        <div class="layui-form-item">
                            <div class="layui-inline">
                                <label class="layui-form-label">通道状态：</label>
                                <div class="layui-input-block">
                                    <input type="checkbox" checked="" name="channel-5_Status" lay-skin="switch" lay-filter="switchTest" lay-text="ON|OFF">
                                </div>
                            </div>

                            <div class="layui-inline layui-col-lg-offset2">
                                <label class="layui-form-label">监控类型:</label>
                                <div class="layui-input-block">
                                    <select name="channel-5_deviceType" lay-filter="channel-5_deviceType">
                                        <option value=""></option>
                                        <option value="枪机" selected="">枪机</option>
                                        <option value="球机" >球机</option>
                                    </select>
                                </div>
                            </div>
                        </div>

                        <div class="layui-form-item">
                            <div class="layui-inline">
                                <label class="layui-form-label">监控地点：</label>
                                <div class="layui-input-block">
                                    <input name="channel-5_monitorPlace" type="text" class="layui-input" placeholder="请输入设备安装地点">
                                </div>
                            </div>

                            <div class="layui-inline">
                                <label class="layui-form-label">协议类型：</label>
                                <div class="layui-input-block">
                                    <input name="channel-5_protocol" type="text" class="layui-input" placeholder="请输入设备协议">
                                </div>
                            </div>
                        </div>

                        <div class="layui-form-item">
                            <div class="layui-inline">
                                <label class="layui-form-label">IP地址：</label>
                                <div class="layui-input-block">
                                    <input name="channel-5_deviceIp" type="text" class="layui-input" placeholder="请输入设备IP地址">
                                </div>
                            </div>

                            <div class="layui-inline">
                                <label class="layui-form-label">端口：</label>
                                <div class="layui-input-block">
                                    <input name="channel-5_devicePort" type="text" class="layui-input" placeholder="请输入设备端口号">
                                </div>
                            </div>
                        </div>

                        <div class="layui-form-item layui-form-text">
                            <label class="layui-form-label">备注：</label>
                            <div class="layui-input-block">
                                <textarea placeholder="请输入备注说明" class="layui-textarea"></textarea>
                            </div>
                        </div>
                    </div>
                    <div class="layui-form-item" id="buttonOpen">
                        <button class="layui-btn" type="submit" lay-submit="" lay-filter="formChannel5">确定</button>
                    </div>
                </fieldset>
            </form>
        </div>
    </div>
</div>
</body>
<script type="text/javascript">
layui.use(['form','layer'], function(){
    var form = layui.form
        ,layer = layui.layer
        ,$ = layui.$;
    form.render();
    form.on('submit(formChannel5)', function(data){
        $.ajax({
            url: '/channel5',
            type: 'POST',
            data: JSON.stringify(data.field),
            success: function(data){
                let res = JSON.parse(data);
                if(res.code === 1 && res.msg === 'ok'){
                    layer.msg('设置成功',{
                        icon: 1,
                        time: 2000
                    })
                }else{
                    layer.msg('设置失败',{
                        icon: 2,
                        time: 2000,
                        shift: 6
                    })
                }
            },
            error: function(){
                layer.msg('服务器连接异常',{
                    icon: 2,
                    time: 2000,
                    shift: 6
                },function(){
                    window.location.reload();
                })
            }
        })
        return false;
    });
});
</script>
</html>
)VOGON";
}

