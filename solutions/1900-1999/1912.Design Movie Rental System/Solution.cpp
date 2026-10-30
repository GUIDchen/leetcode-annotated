// 题目：1912. 设计电影租借系统（Design Movie Rental System）
// 思路：按电影维护有序集合 (price, shop) 表示未租出的店，再维护全局有序集合 (price, shop, movie) 表示已租出记录；search 与 report 都只需按序取前 5。
// 时间复杂度：构造 O(n log n)，search/rent/drop 为 O(log n)，report 为 O(log n + 5)；空间复杂度：O(n)，需要保存全部条目与租借记录。
class MovieRentingSystem {  // 电影租借系统类
private:
    // 电影 -> {(price, shop)}：每部电影当前各店的可租情况
    unordered_map<int, set<pair<int, int>>> available; // movie -> {(price, shop)}  // available 的键是电影编号
    unordered_map<long long, int> priceMap;  // 用 (shop, movie) 编码后的整数作键，值为该片在该店的租金，rent/drop 时据此反查价格
    // 全局已租集合：{(price, shop, movie)}，按价格、商店、电影依次升序
    set<tuple<int, int, int>> rented; // {(price, shop, movie)}  // 已租出记录统一放在这个有序集合里

    long long f(int shop, int movie) {  // 把 (商店编号, 电影编号) 压缩成一个 long long 键，便于用哈希表查价
        return ((long long) shop << 30) | movie;  // 商店编号左移 30 位后与电影编号按位或，两者的二进制位段互不重叠
    }  // 编码函数结束

public:  // 构造与对外接口
    MovieRentingSystem(int n, vector<vector<int>>& entries) {  // n：商店数量（本实现不需要使用）；entries：每项为 [shop, movie, price]
        for (auto& e : entries) {  // 逐条建立索引
            int shop = e[0], movie = e[1], price = e[2];  // 取出当前条目的商店、电影、价格
            available[movie].insert({price, shop});  // 在该电影的可租集合中加入 (价格, 商店)，set 自动按价格、再按商店升序排好
            priceMap[f(shop, movie)] = price;  // 记录这部片在该店的租金，供 rent/drop 使用
        }  // 当前条目处理完毕
    }  // 构造函数结束

    vector<int> search(int movie) {  // 查询某部电影最便宜的 5 家可租商店
        vector<int> res;  // res：保存结果的商店编号
        if (!available.count(movie)) {  // 该电影没有任何可租记录（哈希表里还没有这个键）
            return res;  // 直接返回空列表
        }
        int cnt = 0;  // cnt：已经收集到的商店数量
        for (auto& [price, shop] : available[movie]) {  // 按 (价格, 商店) 升序扫描，天然满足「价格最低、同价取商店编号最小」
            res.push_back(shop);  // 记录这家商店的编号
            if (++cnt == 5) {  // 已经攒够 5 家
                break;  // 提前结束循环
            }
        }
        return res;  // 返回最多 5 家商店（不足 5 家就全部返回）
    }  // search 结束

    void rent(int shop, int movie) {  // 租借：把该片从某店的可租集合移动到全局已租集合
        int price = priceMap[f(shop, movie)];  // 查出租金，它是两个集合排序的第一关键字
        available[movie].erase({price, shop});  // 从该电影的可租集合中删掉这条记录
        rented.insert({price, shop, movie});  // 加入已租集合，report 时会按价格优先被取出
    }  // rent 结束

    void drop(int shop, int movie) {  // 归还：把记录从已租集合移回该店的可租集合
        int price = priceMap[f(shop, movie)];  // 同样先查出这条记录的租金
        rented.erase({price, shop, movie});  // 从已租集合中删除该记录
        available[movie].insert({price, shop});  // 重新放回该电影的可租集合，供后续 search 使用
    }  // drop 结束

    vector<vector<int>> report() {  // 报表：返回租金最低的 5 条已租记录 [shop, movie]
        vector<vector<int>> res;  // res：保存结果的二维列表
        int cnt = 0;  // cnt：已经收集到的记录条数
        for (auto& [price, shop, movie] : rented) {  // 已租集合本身按 (价格, 商店, 电影) 升序，从头依次取即可
            res.push_back({shop, movie});  // 每条记录整理成 [商店, 电影]
            if (++cnt == 5) {  // 已经攒够 5 条
                break;  // 提前结束循环
            }
        }
        return res;  // 返回报表（不足 5 条就全部返回）
    }  // report 结束
};  // 类定义结束

// 以下是题目模板给出的调用示例注释，保留原样
/**
 * Your MovieRentingSystem object will be instantiated and called as such:
 * MovieRentingSystem* obj = new MovieRentingSystem(n, entries);
 * vector<int> param_1 = obj->search(movie);
 * obj->rent(shop,movie);
 * obj->drop(shop,movie);
 * vector<vector<int>> param_4 = obj->report();
 */
