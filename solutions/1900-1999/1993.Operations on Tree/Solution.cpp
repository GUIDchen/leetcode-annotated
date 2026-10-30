// 题目：1993. 树上的操作（Operations on Tree）
// 思路：用 locked 数组记录每个节点的持锁人，用父数组向上回溯、用儿子表向下 DFS。lock/unlock 是一次判断，upgrade 先查祖先全未锁，再 DFS 清空后代的锁。
// 时间复杂度：lock/unlock 为 O(1)，构造为 O(n)，upgrade 最坏为 O(n)；空间复杂度：O(n) 存父数组、锁状态与儿子表。
class LockingTree {  // 关键：维护「每个节点被谁锁住」以及树的两个方向（父亲、儿子）
public:  // 对外暴露构造函数与三个操作
    LockingTree(vector<int>& parent) {  // parent[i] 是节点 i 的父节点，根节点 0 的父节点为 -1
        int n = parent.size();  // 节点个数
        locked = vector<int>(n, -1);  // locked[i] 记录节点 i 的持锁人，-1 表示未上锁
        this->parent = parent;  // 保存父数组，供 upgrade 向上回溯
        children.resize(n);  // 邻接表：children[i] 存放节点 i 的全部儿子
        for (int i = 1; i < n; ++i) {  // 根是 0，所以从 1 开始，把每个节点挂到它的父节点下面
            children[parent[i]].push_back(i);  // 建立向下的边，后面 upgrade 才能 DFS 后代
        }  // 建树结束
    }  // 构造函数结束

    bool lock(int num, int user) {  // lock：给节点 num 上锁，user 是请求者编号
        if (locked[num] == -1) {  // -1 表示当前没有锁，可以上锁
            locked[num] = user;  // 记录锁的持有者
            return true;  // 上锁成功
        }  // 无锁分支结束
        return false;  // 已经被别人锁住，上锁失败
    }  // lock 方法结束

    bool unlock(int num, int user) {  // unlock：只有请求者正是持锁人时才允许解锁
        if (locked[num] == user) {  // 持锁人与请求者一致
            locked[num] = -1;  // 置回 -1，恢复未上锁状态
            return true;  // 解锁成功
        }  // 一致分支结束
        return false;  // 不是持锁人（或本来就没锁），解锁失败
    }  // unlock 方法结束

    bool upgrade(int num, int user) {  // upgrade：要求祖先全部未锁、后代至少有一把锁，然后把后代的锁全部清掉并锁住 num
        int x = num;  // 从 num 出发向上回溯
        while (x != -1) {  // 根节点的父节点是 -1，走到 -1 说明祖先检查完毕
            if (locked[x] != -1) {  // 任一祖先已被锁住
                return false;  // 不满足「祖先全未锁」，升级失败
            }  // 祖先已锁分支结束
            x = parent[x];  // 继续向父节点回溯
        }  // 祖先检查结束
        bool find = false;  // find 标记后代中是否至少有一把锁
        function<void(int)> dfs = [&](int x) {  // 按引用捕获外部变量，定义深度优先遍历的递归 lambda
            for (int y : children[x]) {  // 逐个访问儿子
                if (locked[y] != -1) {  // 儿子当前被锁住
                    find = true;  // 说明确实存在已锁后代
                    locked[y] = -1;  // 顺手清掉这个儿子的锁
                }  // 已锁儿子分支结束
                dfs(y);  // 递归处理更深的后代
            }  // 儿子遍历结束
        };  // lambda 定义结束
        dfs(num);  // 从 num 开始收集并清除后代的锁
        if (!find) {  // 一个已锁后代都没有
            return false;  // 不满足升级条件，失败
        }  // 无锁后代分支结束
        locked[num] = user;  // 条件全部满足，给 num 上锁，持锁人为 user
        return true;  // 升级成功
    }  // upgrade 方法结束

private:  // 以下为私有成员变量
    vector<int> locked;  // 每个节点的持锁人，-1 表示未上锁
    vector<int> parent;  // 父节点数组，用于向上回溯
    vector<vector<int>> children;  // 儿子列表，用于向下遍历
};  // LockingTree 类定义结束

// 下面是 LeetCode 判题器给出的调用示例（保持原样）
/**
 * Your LockingTree object will be instantiated and called as such:
 * LockingTree* obj = new LockingTree(parent);
 * bool param_1 = obj->lock(num,user);
 * bool param_2 = obj->unlock(num,user);
 * bool param_3 = obj->upgrade(num,user);
 */
