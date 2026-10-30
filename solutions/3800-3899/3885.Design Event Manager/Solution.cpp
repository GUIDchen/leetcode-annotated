// 3885. 设计事件管理器 / Design Event Manager
// 核心思路：有序集合存 (-优先级, 事件 id) 天然给出最高优先级，哈希表存 id 到优先级的映射以便 O(1) 定位更新。
// 复杂度：时间 构造 O(n log n)、updatePriority O(log n)、pollHighest O(log n)，空间 O(n)。
class EventManager {  // 事件管理器
public:  // 公有接口
    set<pair<int, int>> sl;  // 有序集合，按 (-优先级, 事件 id) 升序排列
    unordered_map<int, int> d;  // 事件 id 到当前优先级的映射

    EventManager(vector<vector<int>>& events) {  // 构造函数：用初始事件列表建表
        for (auto& e : events) {  // 遍历事件列表
            int eventId = e[0], priority = e[1];  // 取出事件 id 与优先级
            sl.insert({-priority, eventId});  // 取负优先级实现降序，同优先级按 id 升序
            d[eventId] = priority;  // 记录该事件的优先级
        }  // 遍历结束
    }  // 构造函数结束

    void updatePriority(int eventId, int newPriority) {  // 更新指定事件的优先级
        int old = d[eventId];  // 取出旧优先级
        sl.erase({-old, eventId});  // 从有序集合中删除旧条目
        sl.insert({-newPriority, eventId});  // 插入新优先级对应的条目
        d[eventId] = newPriority;  // 同步哈希表中的优先级
    }  // 方法结束

    int pollHighest() {  // 取出并删除优先级最高的事件 id
        if (sl.empty()) {  // 集合为空说明没有事件
            return -1;  // 没有可取出的事件，返回 -1
        }  // 空判断结束
        auto it = sl.begin();  // 首元素即优先级最高（同优先级 id 最小）
        int eventId = it->second;  // 取出事件 id
        sl.erase(it);  // 从有序集合中删除该条目
        d.erase(eventId);  // 从哈希表中删除该事件
        return eventId;  // 返回被取出的事件 id
    }  // 方法结束
};  // 类定义结束

/**
 * Your EventManager object will be instantiated and called as such:
 * EventManager* obj = new EventManager(events);
 * obj->updatePriority(eventId,newPriority);
 * int param_2 = obj->pollHighest();
 */
