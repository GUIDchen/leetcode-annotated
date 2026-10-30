# 3885. 设计事件管理器 / Design Event Manager
# 核心思路：有序列表存 (-优先级, 事件 id) 直接给出最高优先级，字典存 id 到优先级以便 O(1) 定位更新。
# 复杂度：时间 构造 O(n log n)、updatePriority O(log n)、pollHighest O(log n)，空间 O(n)。
class EventManager:  # 事件管理器

    def __init__(self, events: list[list[int]]):  # 构造函数：用初始事件列表建表
        self.sl = SortedList()  # 有序列表，按 (-优先级, 事件 id) 升序排列
        self.d = {}  # 事件 id 到当前优先级的映射
        for eventId, priority in events:  # 遍历事件列表
            self.sl.add((-priority, eventId))  # 取负优先级实现降序，同优先级按 id 升序
            self.d[eventId] = priority  # 记录该事件的优先级

    def updatePriority(self, eventId: int, newPriority: int) -> None:  # 更新指定事件的优先级
        old_priority = self.d[eventId]  # 取出旧优先级
        self.sl.remove((-old_priority, eventId))  # 从有序列表中删除旧条目
        self.sl.add((-newPriority, eventId))  # 插入新优先级对应的条目
        self.d[eventId] = newPriority  # 同步字典中的优先级

    def pollHighest(self) -> int:  # 取出并删除优先级最高的事件 id
        if not self.sl:  # 列表为空说明没有事件
            return -1  # 没有可取出的事件，返回 -1
        eventId = self.sl.pop(0)[1]  # 弹出首元素（优先级最高）并取事件 id
        self.d.pop(eventId)  # 从字典中删除该事件
        return eventId  # 返回被取出的事件 id


# Your EventManager object will be instantiated and called as such:
# obj = EventManager(events)
# obj.updatePriority(eventId,newPriority)
# param_2 = obj.pollHighest()
