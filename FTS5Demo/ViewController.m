//
//  ViewController.m
//  FTS5Demo
//
//  Created by Xu Menghua on 2017/12/25.
//  Copyright © 2017年 Xu Menghua. All rights reserved.
//

#import "ViewController.h"
#import "SqliteFTSManager.h"
#import "sqlite_fts_util.h"
#import "SqliteFTSUtil.h"
#import <CoreFoundation/CoreFoundation.h>
#import <Foundation/Foundation.h>

@interface ViewController ()

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
    [[SqliteFTSManager sharedManager] initFTS];
    [self prepareTestData];
    [self testMatch];
}


- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (void)prepareTestData {
    NSLog(@"prepare test data started");
    NSDate *startTime = [NSDate date];
    NSString *text = @"江氏的传记《他改变了中国：江泽民传》，其熟稔的歌曲（如《毕业歌》、《Aloha ʻOe》、《One day when we were young》、《Love Me Tender》），其诗作（如《满江红·江上青百年诞辰祭》、《登黄山偶感》、《七律·园竹》），其讲话中曾引用的文章（如《葛底斯堡演说》）及前人诗句（林则徐《赴戍登程口占示家人》）乃至其曾提及的数学问题（如密克定理中的五点共圆问题）[3]，1993年春节联欢晚会中走访窦店村的视频片段以及传说中江氏居住的301医院以及几位与其传有绯闻的女性等，也成为膜蛤的素材。例如2011年时杨澜、宋祖英、苍井空三人并排站立的一张照片就被网友调侃为“三个代表”[4]。同时薄熙来的部分语录（如：说“我儿子开红色法拉利”、“一派胡言”、“靡靡之音，轻歌曼舞”、“就是得豪迈”、“给我泼脏水”、“敢同恶鬼争高下，不向霸王让寸分”、“踢断肋骨”等）也被蛤丝广泛使用，称为“膜督”。由于薄氏的处事原则在很多方面都类似于江氏，所以部分蛤丝也参与膜督，因此也成为膜蛤文化的一部分。而膜督文化的主要来源就是薄熙来在新闻发布会上的发言，因薄曾担任省委书记、市委书记，如同总督，所以“督”暗指薄熙来。又因其最后担任的公职是重庆市委书记，加以在重庆唱红打黑，只手遮天，于是又有人冠以“平西王”（吴三桂的封号）的称号。此外，涉及到六四事件相关的言论也会被掺入到膜蛤文化中，比如称王维林为“螳臂当车的歹徒”、“如果我们的铁骑继续前进”等等（均出自中共纪录片《共和国卫士》中的解说）。另外，类似的对现任中国国家领导人习近平的调侃模因则被称为“辱包”（“包”隐喻习近平，来源于对习近平吃包子事件的调侃），也成为膜蛤文化的一部分，相当一部分蛤丝膜蛤的同时也参与“辱包”。比如在互动平台中宣扬习近平的错读“轻关易道，通商宽衣”这一句话，以及网友改编歌手吴克群的歌曲《为你写诗》中的歌词：“维尼写诗，维尼禁止，维尼做不可能的事，维尼失去理智。”（因著名卡通人物小熊维尼与习的形象神似，常被网友用作指代习）此歌词讽刺习近平上任后中国的公共言论审查力度加大，并常有异议批评其有开历史倒车、逆行倒施的嫌疑（如鼓动民众对习近平的个人崇拜等）。与维尼隐喻类似的还有“枪毙名单”、“查水表”、“社区送温暖”、“请去喝茶”、“妄议朝廷”等，都被用来暗指在中国“因言获罪”的现象，即批评中国政治或评论社会议题所可能招致不良后果，如行政拘留，封禁社交平台账号，甚至判处监禁等惩罚。高校学生群体内广泛存在着膜蛤现象。比如江曾经求学的上海交通大学，其电气工程系（前身为上海交大电机系）被学生蛤丝群体调侃为“膜法系”。在一些航空类团体内，江曾经乘坐的B-2447(747-4J6)和B-2499(767-332)，甚至是夏威夷注册号NXXXHA(最典型的例子是N817HA，因江生日是8月17日)，伊比利亚航空一架321的注册号EC-JZM，南航几架330CEO的注册号B-5959、B-6059（暗示六四事件中的59坦克）；加拿大航空的新涂装风挡的黑框涂装、330NEO和350的黑框风挡（“黑框眼镜”）均可以被用于膜蛤。此外，ANA注册号为JA8964的747-481D和首都航空“膜法世家”彩绘机(A320，注册号B-6795)也被用作了直接膜蛤的元素。本田在日本本土生产发售的车型N-ONE因为前脸酷似戴黑框眼镜的青蛙，也成为部分汽车爱好者的膜蛤素材，甚至在在日中国留学生群体中出现了在街上看到N-ONE就跑开的现象（意为“害怕被‘续命’”）。[来源请求]同样成为膜蛤素材的车型还有铃木Hustler、大发CAST（容易让人联想到“闷声大发财”）、保时捷的大部分车型等等其他带有圆形车灯的车款，因为圆形车灯可以让人联想起青蛙。其中Hustler因为车名可以被音译成“蛤丝乐”，被众多车迷一致认为是最为“危险”的车款之一，“看到之后寿命流逝速度并不低于N-ONE”。维基语录上的相关摘录：怒斥香港记者维基语录上的相关摘录：麦克·华莱士访谈维基语录上的相关摘录：视察联工国机二院在网络上的一些含有酷似江的形象的图片，常被用于膜蛤：如放置着黑框眼镜的篮球、栏杆的铁链、雅哈冰咖啡的品牌标志、只露出黑框眼镜和眼睛的李嘉诚照片、用计算器键盘上的数学符号和字母拼出江的形象等。网络上三段与江泽民有关的视频被广泛用于模仿恶搞（俗称“蛤三篇”），分别是：1、怒斥记者——2000年10月27日，江泽民在中南海怒斥香港记者张宝华；2、谈笑风生——2000年8月15日，迈克·华莱士在北戴河访问江泽民；3、视察二院——2009年4月23日，江泽民以前党和国家领导人身份视察国机二院。其中，蛤三篇引出了很多单个素材，如：我不是新闻工作者，但是我见得太多了";
    NSMutableArray *dataArray = [NSMutableArray array];
    for (int i = 0; i < 10000; i++) {
        NSUInteger location = arc4random() % text.length;
        NSUInteger length = arc4random() % (text.length - location);
        NSRange range = NSMakeRange(location, length);
        NSString *messageId = [NSString stringWithFormat:@"%06d", i];
        NSString *message = [text substringWithRange:range];
        NSDictionary *data = @{@"type":@"1", @"col1":message, @"uCol1":messageId};
        [dataArray addObject:data];
    }
    if ([SqliteFTSUtil insertArrayToFts:dataArray] != SQLITE_OK) {
        NSLog(@"prepare test data error");
    }
    NSDate *finishTime = [NSDate date];
    NSTimeInterval time = [finishTime timeIntervalSinceDate:startTime];
    NSLog(@"time:%lf", time);
    NSLog(@"prepare test data finished");
    NSLog(@"data path:%@", [NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES) firstObject]);
}

- (void)testMatch {
    NSLog(@"data path:%@", [NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES) firstObject]);
    NSDate *startTime = [NSDate date];
    NSLog(@"match started");
    NSArray *result = [SqliteFTSUtil selectWithTable:@"fts" Column:@"fts" Match:@"江泽民"];
    NSDate *finishTime = [NSDate date];
    NSTimeInterval time = [finishTime timeIntervalSinceDate:startTime];
    NSLog(@"match finished");
    NSLog(@"time:%lf", time);
    NSLog(@"result list count:%ld", result.count);
}

@end
