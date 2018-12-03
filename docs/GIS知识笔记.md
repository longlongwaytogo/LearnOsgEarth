# GIS知识笔记

## 1.地图瓦片

如今互联网地图的地图内容分为两种，一种是栅格地图瓦片，一种是矢量地图瓦片。

### 栅格地图瓦片
栅格地图瓦片是一种比较传统的模式，将矢量数据渲染成为256×256像素大小的图片。前端js地图框架，如openlayer和leaflet，按一定规则编排显示，如百度地图，高德地图，天地图等。栅格瓦片地图的渲染技术已经成熟，可以实现栅格渲染，矢量渲染两种。参考笔记mapnik 笔记一: 入门及python接口使用。

[来源](https://www.jianshu.com/p/59d4ab010ee9)


## 矢量地图瓦片
矢量地图瓦片是一种新颖的模式。地图数据会以json等格式分块地传输过去，在浏览器端利用前端框架将地图在显示出来。在这个基础上，你必须懂得canvas。整个展示的过程对点线面的渲染有很严格的规定。总体来说，矢量瓦片的数据传输量少，服务器压力小。方便渲染成为各种各样的地图，所以这也是为什么Mapbox首推Mapbox GL的原因，腾讯地图使用矢量渲染的原因。而且现在移动端不断利用矢量瓦片的技术，考虑到导航时候，需要将地图旋转成为伪3D界面。

[链接](https://www.jianshu.com/p/59d4ab010ee9)


## 2 EPSG
EPSG（The European Petroleum Survey Group, http://www.epsg.org/ ）维护着空间参照对象的数据集，OGC标准中空间参照系统的SRID（Spatial Reference System Identifier）与EPSG的空间参照系统ID相一致。
update090601:http://www.epsg-registry.org 和 http://spatialreference.org/ 可以由SRID查询相应 的空间参考系的参数，以及WKT、proj4等多种表达方式。当然有许多开源小工具库也支持相应的转换。
EPSG成立于1986年，并已于2005年“重组”为The OGP Surveying and Positioning Committee，维护并发布坐标参照系统的数据集参数，以及坐标转换描述。该数据集被广泛接受并使用，通过一个Web发布平台进行分发，同时提供了微软Acess数据库的存储文件，通过SQL 脚本文件，mySQL, Oracle 和PostgreSQL等数据库也可使用。详细请参考：http://www.epsg.org/Geodetic.html
由于EPSG提供的是Acess 97的数据库，LionGG用Acess 2007打开时出现了部分转换错误，只能看到部分表。但不影响理解和使用，只需要理解特定的ID代表特定的椭球体、单位、地理坐标系或投影坐标系等，然后在使用中正确的援引ID来使用相关对象。
以 PROJCS["WGS 84 / UTM zone 50N"] ( WGS1984地理坐标，统一横轴墨卡托(UTM)投影，中央经线117E的投影坐标系) 的 WKT (Well Known Text) 形式为例来解释：
PROJCS["WGS 84 / UTM zone 50N",
GEOGCS["WGS 84", DATUM["WGS_1984", SPHEROID["WGS 84", 6378137, 298.257223563, AUTHORITY["EPSG", "7030"]], AUTHORITY["EPSG", "6326"]], PRIMEM["Greenwich", 0, AUTHORITY["EPSG", "8901"]], UNIT["degree", 0.0174532925199433, AUTHORITY["EPSG", "9122"]], AUTHORITY["EPSG", "4326"]],
PROJECTION["Transverse_Mercator"],
PARAMETER["latitude_of_origin", 0],
PARAMETER["central_meridian", 117],
PARAMETER["scale_factor", 0.9996],
PARAMETER["false_easting", 500000],
PARAMETER["false_northing", 0],
UNIT["metre", 1, AUTHORITY["EPSG", "9001"]],
AUTHORITY["EPSG", "32650"]]
AUTHORITY["EPSG", "9122"]指的是EPSG数据集中UNIT为degree的ID是9122；AUTHORITY["EPSG", "4326"]指的是地理坐标系WGS 84的ID是4326；AUTHORITY["EPSG", "9001"]指的是EPSG中UNIT为meter的ID是9001；AUTHORITY["EPSG", "32650"]指的是该投影坐标系WGS 84 / UTM zone 50N的ID是32650。其他的类似，下表示意相关ID的取值范围。
在进行简单操作时调用数据库可能显得麻烦，ProjNET为我们提供了一个SRID.csv文件，文件中每一行对应一个坐标系，每行又SRID和对应坐标系的WKT形式组成。因此可以很方便地通过SRID来获取地理坐标系或投影坐标系，《Loading a projection by Spatial Reference ID》提供了一个SridReader类来实现GetCSbyID返回相应坐标系的功能。SRID.csv和SRIDReader.cs在ProjNET源码和示例中可下载得到。
参考资料： [http://apps.hi.baidu.com/share/detail/33108874]()

## 3. WKT

WKT(Well-known text)是一种文本标记语言，用于表示矢量几何对象、空间参照系统及空间参照系统之间的转换。它的二进制表示方式，亦即WKB(well-known-binary)则胜于在传输和在数据库中存储相同的信息。该格式由开放地理空间联盟(OGC)制定。WKT可以表示的几何对象包括：点，线，多边形，TIN（不规则三角网）及多面体。以下为几何WKT字串样
例： 

		POINT(6 10) 
		LINESTRING(3 4,10 50,20 25) 
		POLYGON((1 1,5 1,5 5,1 5,1 1),(2 2,2 3,3 3,3 2,2 2)) 
		MULTIPOINT(3.5 5.6, 4.8 10.5) 
		MULTILINESTRING((3 4,10 50,20 25),(-5 -8,-10 -8,-15 -4)) 
		MULTIPOLYGON(((1 1,5 1,5 5,1 5,1 1),(2 2,2 3,3 3,3 2,2 2)),((6 3,9 2,9 4,6 3))) 
		GEOMETRYCOLLECTION(POINT(4 6),LINESTRING(4 6,7 10)) 
		POINT ZM (1 1 5 60) 
		POINT M (1 1 80) 
		POINT EMPTY 
		MULTIPOLYGON EMPTY


来源: [https://blog.csdn.net/mwp5212/article/details/77448008]()

## 4. UTM简介

UTM (Universal Transverse Mercator)坐标系是由美国军方在1947提出的。虽然我们仍然将其看作与“高斯－克吕格”相似的坐标系统，但实际上UTM采用了网格的分带（或分块）。除在美国本土采用Clarke 1866椭球体以外，UTM在世界其他地方都采用WGS84。 UTM是由美国制定，因此起始分带并不在本初子午线，而是在180度，因而所有美国本土都处于0－30带内。UTM投影采用6度分带，从东经180度（或西经180度）开始，自西向东算起，因此1带的中央经线为-177（-180 -(-6)），而0度经线为30带和31带的分界，这两带的分界分别是-3和3度。纬度采用8度分带，从80S到84N共20个纬度带（X带多4度），分别用C到X的字母来表示。为了避免和数字混淆，I和O没有采用。UTM的“false easting”值为500km，而南半球UTM带的“false northing”为10000km.。
来源：[https://blog.csdn.net/ivan_ljf/article/details/52637293]()

## 5. 大地坐标高斯/UTM投影计算工具
[https://blog.csdn.net/qq_22865459/article/details/80390653]()