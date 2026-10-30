// 3829. 设计共享出行系统 / Design Ride Sharing System（中等）
// 核心思路：用全局自增序号 t 标记加入顺序，骑手与司机各存 (t, id) 有序集合，匹配时各取最小序号即先到先服务；另用哈希表记录骑手序号以支持取消。
// 复杂度：addRider/addDriver/cancelRider 均 O(log n)，matchDriverWithRider 为 O(log n)；空间 O(n)。
class RideSharingSystem {  // 设计共享出行系统：骑手排队等司机，司机排队等骑手
private:  // 私有成员区
    int t;  // 全局自增序号，代表加入时间的先后顺序
    set<pair<int, int>> riders;  // 骑手集合，(加入序号, 骑手 id)，按序号升序即为先到先服务
    set<pair<int, int>> drivers;  // 司机集合，(加入序号, 司机 id)，同样按序号升序排队
    unordered_map<int, int> d;  // 骑手 id → 其加入序号，取消时用来定位集合中的元素

public:  // 对外接口区
    RideSharingSystem() {  // 构造函数：系统初始为空
        t = 0;  // 序号从 0 开始
    }

    void addRider(int riderId) {  // 新增一名等待中的骑手
        d[riderId] = t;  // 记录该骑手对应的加入序号
        riders.insert({t, riderId});  // 把 (序号, id) 插入有序集合，序号越小越靠前
        t++;  // 序号自增，保证全局单调递增
    }

    void addDriver(int driverId) {  // 新增一名等待中的司机
        drivers.insert({t, driverId});  // 把 (序号, id) 插入司机有序集合
        t++;  // 序号同样自增，与骑手共用同一条时间线
    }

    vector<int> matchDriverWithRider() {  // 为最早等待的司机匹配最早等待的骑手
        if (riders.empty() || drivers.empty()) {  // 任意一方无人等待时无法匹配
            return {-1, -1};  // 无匹配时按约定返回 {-1, -1}
        }
        int driverId = drivers.begin()->second;  // 司机集合首元素即序号最小（等待最久）的司机
        int riderId = riders.begin()->second;  // 骑手集合首元素即序号最小（等待最久）的骑手
        drivers.erase(drivers.begin());  // 从司机集合中删除已匹配的司机
        riders.erase(riders.begin());  // 从骑手集合中删除已匹配的骑手
        return {driverId, riderId};  // 返回匹配到的司机与骑手编号
    }

    void cancelRider(int riderId) {  // 取消某骑手的等待请求
        auto it = d.find(riderId);  // 在哈希表中查找该骑手的加入序号
        if (it != d.end()) {  // 只有该骑手确实在等待时才需要删除
            riders.erase({it->second, riderId});  // 用 (序号, id) 精确定位并从集合中删除
        }
    }
};

/**
 * Your RideSharingSystem object will be instantiated and called as such:
 * RideSharingSystem* obj = new RideSharingSystem();
 * obj->addRider(riderId);
 * obj->addDriver(driverId);
 * vector<int> param_3 = obj->matchDriverWithRider();
 * obj->cancelRider(riderId);
 */
