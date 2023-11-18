# hx_malloc
练手的内存管理

##关于二维数组
二维数组a[][] ：
二维数组a本质上是指向指针的指针，正如一维数组也是指针一样，所以*a其实是指向一个一维数组是指针。
同时二维数组在内存上是连续的，可以使用memset来设置初值也可以使用来清0

以下是int a[3][4]在内存中存储布局的示意：
a[0][0] a[0][1] a[0][2] a[0][3] a[1][0] a[1][1] a[1][2] a[1][3] a[2][0] a[2][1] a[2][2] a[2][3]

##关于hx_malloc内存分配
内存分配是通过声明一个大数组，数组内每个小单位是1Byte，通过对这个大数组内的管理实现的内存分配
内存管理表：用于指示大数组中的哪些部分是否已被分配
    内存管理表也是一个数组，内存管理表中的每个小单位虽然也是1Byte，然而确是按照1：8对大数组进行映射的，即内存管理表的1bit若为1代表大数组的的一个byte已被使用。

由于内存的使用必须是连续的，所以my_malloc函数通过逐个检索内存管理表中的每个bit，如果为空，就将计数值加一，若计数值达到需求值，则代表有达到需求的连续存储空间，将这块空间的开头地址返回给请求源，并将内存管理表中的对应位置置1表示这块内存已被使用，不能被二次使用
当需要释放内存时就将内存管理器的对应位置置0，这块内存就可被再次分配给其他请求源，但是此时这块内存可能仍然残留有上次使用的数据，根据需要可在分配后对这块内存先使用memset先清空，防止不可预料的情况

关于请求源：请求源是一个句柄，代表了被分配的内存的信息
+ *pos代表了被分配内存的起始地址
+ beginPos代表了被分配的内存在大数组中的序号
+ length代表了被分配内存的长度
请求源被创建后调用句柄处理函数NewMemHandler()即可初始化并分配内存

