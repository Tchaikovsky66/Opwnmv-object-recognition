import sensor,image,time,math,json
from pyb import UART

green_threshold  = (0, 58, -49, -19, 39, -17)
red_thresholds  = (0, 100, 7, 127, -128, 127)

#基本参数设置
sensor.reset()
sensor.set_pixformat(sensor.RGB565)#设置图像色彩格式，有RGB565色彩图和GRAYSCALE灰度图两种
sensor.set_framesize(sensor.QQVGA)#设置图像大小
sensor.skip_frames(time = 2000) #跳过前2000ms的图像
#sensor.set_auto_whitebal(False)#关闭白平衡
clock = time.clock()# 跟踪FPS帧率

uart = UART(3,115200)
uart.init(115200,bits = 8,parity = None,stop = 1)

def find_max(blobs):                           #定义函数选取元素面积最大
    max_size = 0                               #初值为0
    for blob in blobs:                         #for循环迭代
        if blob[2]*blob[3] > max_size:         #被测物体面积 = blob[2]*blob[3]
            max_blob = blob
            max_size = blob[2]*blob[3]
    return max_blob                            #将最大元素值返回

K1 = 500   #每次改变物体，K值都要重新计算 K1 = 距离（25cm已知）*直径像素Lm（20)
K2 = 0.16  #实际距离 = k * 直径的像素,K2 = 实际大小（宽4cm已知）/宽像素b[2]（25）
K3 = 0.16  #实际距离 = k * 直径的像素,K3 = 实际大小（长4cm已知）/长像素b[3]（25）

while(True):
    data = []
    img = sensor.snapshot()
    blobs = img.find_blobs([red_thresholds])
    if blobs:
            max_blob = find_max(blobs)

            Lm = (max_blob.w() + max_blob.h())/2 #色块的长与宽 直径像素点个数
            length = K1 / Lm
            width = K2 * max_blob.w()
            height = K3 * max_blob.h()

            img.draw_cross(int(max_blob[5]),int(max_blob[6]),color=(0,255,0))#色块中心坐标CX,CY
            img.draw_rectangle(max_blob.rect())

            data = bytearray([0xb3,0xb3,max_blob[5],max_blob[6],int(length),0x0d,0x0a])
            uart.write(data)
            print("cx:%d,cy:%d"%(max_blob[5],max_blob[6]))#将色块中心坐标输出
            print("lenght: %s cm"%(int(length)))
            print("宽是:%s cm, 长是:%s cm"%(width,height))   #测量物体大小
    print(data)
    print("**************************************")
