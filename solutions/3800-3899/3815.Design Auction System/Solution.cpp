// 题目：3815. 设计拍卖系统（Design Auction System）
// 思路：双向索引。users[userId][itemId] 记录该用户对该物品的出价，items[itemId] 是「(出价, 用户)」的有序集合，按出价升序排列。每次新增或改价都先删旧记录再插新记录，最高出价者直接取集合尾部元素的用户编号。
// 时间复杂度：addBid/updateBid/removeBid 均为 O(log m)，getHighestBidder 为 O(1)；空间复杂度：O(k)，k 为当前有效出价总数。
class AuctionSystem {  // LeetCode 约定的设计类
    unordered_map<int, set<pair<int, int>>> items;  // itemId -> 有序集合{(出价, userId)}，按出价升序，便于取最大值
    unordered_map<int, unordered_map<int, int>> users;  // userId -> (itemId -> 出价)，用于 O(1) 查到旧出价

public:  // 以下是对外提供的接口
    AuctionSystem() {  // 构造函数，容器由默认构造自动初始化，无需额外工作
    }

    void addBid(int userId, int itemId, int bidAmount) {  // 为某用户对某物品新增一次出价
        if (users[userId].count(itemId)) {  // 该用户对这件物品之前已经出过价
            removeBid(userId, itemId);  // 先撤销旧出价，保证每人对每件物品只保留一条记录
        }
        users[userId][itemId] = bidAmount;  // 记录该用户对这件物品的新出价
        items[itemId].insert({bidAmount, userId});  // 同时把 (出价, 用户) 放进该物品的有序集合
    }

    void updateBid(int userId, int itemId, int newAmount) {  // 修改一条已有的出价
        int oldAmount = users[userId][itemId];  // 取出旧出价，用于在有序集合中定位旧的二元组
        auto& s = items[itemId];  // 拿到该物品的有序集合引用，避免反复做哈希查找
        s.erase({oldAmount, userId});  // 从有序集合中删掉旧出价记录
        s.insert({newAmount, userId});  // 插入新出价记录，set 会自动保持按出价有序
        users[userId][itemId] = newAmount;  // 同步更新用户维度的出价
    }

    void removeBid(int userId, int itemId) {  // 撤销一条出价
        int oldAmount = users[userId][itemId];  // 取出该用户对该物品的当前出价
        auto& s = items[itemId];  // 拿到该物品的有序集合引用
        s.erase({oldAmount, userId});  // 从有序集合中删除这条出价
        users[userId].erase(itemId);  // 再从用户维度删除这件物品，表示该用户已无出价
    }

    int getHighestBidder(int itemId) {  // 查询某件物品的最高出价者
        auto it = items.find(itemId);  // 查找该物品的出价集合
        if (it == items.end() || it->second.empty()) {  // 物品从未被出价，或当前没有任何有效出价
            return -1;  // 按题目要求返回 -1
        }
        return it->second.rbegin()->second;  // 集合按出价升序，反向迭代器的首元素就是最高出价，取其 userId
    }
};

/**
 * Your AuctionSystem object will be instantiated and called as such:
 * AuctionSystem* obj = new AuctionSystem();
 * obj->addBid(userId,itemId,bidAmount);
 * obj->updateBid(userId,itemId,newAmount);
 * obj->removeBid(userId,itemId);
 * int param_4 = obj->getHighestBidder(itemId);
 */  // 上面这段是 LeetCode 判题器的固定调用模板注释
