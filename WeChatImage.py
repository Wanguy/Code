import itchat
import math
import PIL.Image as Image
import os



itchat.auto_login(enableCmdQR=2)
friends = itchat.get_friends(update=True)[0:]
user = friends[0]["UserName"]

num = 0
for i in friends:
    print '----> %d' % num
    img = itchat.get_head_img(userName=i["UserName"])
    fileImage = open('/Users/sephiroth/Desktop/wc' + "/" + str(num) + ".jpg", 'wb')
    fileImage.write(img)
    fileImage.close()
    num += 1

ls = os.listdir('/Users/sephiroth/Desktop/wc')

lenls = len(ls)

err = 0

for i in range(0, len(ls) + 1):
    try:
        img = Image.open('/usr/test/image' + "/" + str(i) + ".jpg")
    except IOError:
        #  print("Error")
        err += 1

# print err


##计算图形排列
picnum = math.ceil(math.sqrt(lenls - err))

lines = int(640 / picnum)

image = Image.new('RGBA', (640, 640))
x = 0
y = 0
for i in range(0, len(ls) + 1):
    try:
        img = Image.open('/usr/test/image' + "/" + str(i) + ".jpg")
    except IOError:
        print("pic :( ")
    else:
        img = img.resize((lines, lines), Image.ANTIALIAS)
        image.paste(img, (x * lines, y * lines))
        x += 1
        if x == picnum:
            x = 0
            y += 1
image.save('/Users/sephiroth/Desktop/wc' + "/" + "all.jpg")
itchat.send_image('/Users/sephiroth/Desktop/wc' + "/" + "all.jpg", 'filehelper')

print 'Finish!'
