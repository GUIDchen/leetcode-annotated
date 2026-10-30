# 题目：2590. 设计一个待办事项清单（Design a Todo List）
# 思路：为每个用户维护一个按截止日期有序的列表，任务存成 [dueDate, 描述, 标签集合, id, 是否完成]；完成时按 id 找到并打标记，查询时过滤掉已完成项。
# 时间复杂度：addTask/getAllTasks/getTasksForTag/completeTask 均摊 O(log n + k)，k 为返回或扫描的条数；空间复杂度：O(总任务数)。
class TodoList:  # 待办清单类，每个用户一条有序列表
    def __init__(self):  # 构造函数：初始化自增编号与用户到任务列表的映射
        self.i = 1  # 全局自增的任务编号，从 1 开始
        self.tasks = defaultdict(SortedList)  # 用户 id -> 有序列表，元素是 [dueDate, 描述, 标签集, 任务 id, 是否完成]

    def addTask(  # 新增任务：返回系统分配的 taskId
        self, userId: int, taskDescription: str, dueDate: int, tags: List[str]  # 用户 id、任务描述、截止日期、标签列表
    ) -> int:  # 返回新任务的编号
        taskId = self.i  # 先记下本次要分配的编号
        self.i += 1  # 编号自增，供下一个任务使用
        self.tasks[userId].add([dueDate, taskDescription, set(tags), taskId, False])  # 插入有序列表：按 dueDate 排序，标签转成集合便于 O(1) 查询，完成标记初始为 False
        return taskId  # 返回分配给该任务的编号

    def getAllTasks(self, userId: int) -> List[str]:  # 取该用户所有未完成任务的描述
        return [x[1] for x in self.tasks[userId] if not x[4]]  # 有序列表天然按截止日期升序，过滤掉已完成的项后取描述 x[1]

    def getTasksForTag(self, userId: int, tag: str) -> List[str]:  # 取该用户带有指定标签的未完成任务描述
        return [x[1] for x in self.tasks[userId] if not x[4] and tag in x[2]]  # 同时满足「未完成」与「标签集合包含 tag」两个条件

    def completeTask(self, userId: int, taskId: int) -> None:  # 把指定任务标记为已完成
        for task in self.tasks[userId]:  # 线性扫描该用户的任务列表
            if task[3] == taskId:  # 找到 id 匹配的那条任务
                task[4] = True  # 就地修改第 5 个字段，把完成标记置为 True
                break  # 编号唯一，找到即可提前退出


# Your TodoList object will be instantiated and called as such:
# obj = TodoList()
# param_1 = obj.addTask(userId,taskDescription,dueDate,tags)
# param_2 = obj.getAllTasks(userId)
# param_3 = obj.getTasksForTag(userId,tag)
# obj.completeTask(userId,taskId)