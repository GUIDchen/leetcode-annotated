// 3822. Design Order Management System | 3822. 设计订单管理系统
// 核心思路：两张哈希表记录每单的类型与价格，再用 (类型, 价格) -> 订单列表 的哈希索引支持按价位查询
// 复杂度：addOrder / getOrdersAtPrice 均摊 O(1)，modifyOrder / cancelOrder 为同价位列表线性 O(L)
class OrderManagementSystem {  // 订单管理系统：按订单类型与价格维护订单，并支持按价位查询
    using Key = pair<string, int>;  // 哈希索引的键：订单类型 + 价格

    struct KeyHash {  // pair 没有内置哈希，这里自定义一个仿函数
        size_t operator()(const Key& k) const {  // 计算键 (类型, 价格) 的哈希值
            return hash<string>()(k.first) ^ (hash<int>()(k.second) << 1);  // 类型哈希与左移一位后的价格哈希做异或，减少冲突
        }
    };

    unordered_map<int, string> orderTypeMap;  // orderId -> 订单类型
    unordered_map<int, int> priceMap;  // orderId -> 价格
    unordered_map<Key, vector<int>, KeyHash> t;  // (类型, 价格) -> 该价位的订单 id 列表（按加入先后顺序）

public:
    OrderManagementSystem() {}  // 构造函数：使用默认初始化的成员即可，无需额外操作

    void addOrder(int orderId, string orderType, int price) {  // 新增订单
        orderTypeMap[orderId] = orderType;  // 记录订单类型
        priceMap[orderId] = price;  // 记录订单价格
        t[{orderType, price}].push_back(orderId);  // 把订单 id 追加到对应价位的列表尾部
    }

    void modifyOrder(int orderId, int newPrice) {  // 修改订单价格为 newPrice
        string orderType = orderTypeMap[orderId];  // 取出该订单的类型
        int oldPrice = priceMap[orderId];  // 取出该订单的旧价格
        priceMap[orderId] = newPrice;  // 把价格表里的价格更新为新价格

        auto& oldList = t[{orderType, oldPrice}];  // 旧价位对应的订单列表
        oldList.erase(find(oldList.begin(), oldList.end(), orderId));  // 从旧价位列表中找到并删除该订单 id

        t[{orderType, newPrice}].push_back(orderId);  // 追加到新价位的订单列表尾部
    }

    void cancelOrder(int orderId) {  // 取消订单
        string orderType = orderTypeMap[orderId];  // 取出该订单的类型
        int price = priceMap[orderId];  // 取出该订单的价格

        orderTypeMap.erase(orderId);  // 从类型表中删除该订单
        priceMap.erase(orderId);  // 从价格表中删除该订单

        auto& list = t[{orderType, price}];  // 该价位对应的订单列表
        list.erase(find(list.begin(), list.end(), orderId));  // 从列表中删除该订单 id
    }

    vector<int> getOrdersAtPrice(string orderType, int price) {  // 查询某类型某价格下的所有订单 id
        auto it = t.find({orderType, price});  // 在哈希索引里查找对应的订单列表
        if (it == t.end()) return {};  // 没有该价位的订单则返回空列表
        return it->second;  // 返回该价位的订单 id 列表
    }
};

/**
 * Your OrderManagementSystem object will be instantiated and called as such:
 * OrderManagementSystem* obj = new OrderManagementSystem();
 * obj->addOrder(orderId,orderType,price);
 * obj->modifyOrder(orderId,newPrice);
 * obj->cancelOrder(orderId);
 * vector<int> param_4 = obj->getOrdersAtPrice(orderType,price);
 */
