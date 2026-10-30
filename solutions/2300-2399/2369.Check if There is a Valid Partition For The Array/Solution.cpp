// 题目：2369. 检查数组是否存在有效划分（Check if There is a Valid Partition For The Array）
// 核心思路：记忆化 DFS 从下标 i 出发尝试三种合法切法（两数相等 / 三数相等 / 三数连续递增 1），任一能走到末尾即成功。
// 时间复杂度：O(n)，每个下标只计算一次；空间复杂度：O(n)，记忆化数组与递归栈。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    bool validPartition(vector<int>& nums) {  // 判断 nums 能否被完整划分成若干合法小段
        n = nums.size();  // 把长度存进成员变量，供后面的 dfs 直接使用
        this->nums = nums;  // 输入数组也存成成员变量，dfs 就不用反复传参
        f.assign(n, -1);  // 记忆化数组初始化为 -1，表示「该状态还没算过」
        return dfs(0);  // 从下标 0 开始尝试划分
    }  // 方法结束

private:  // 以下成员只给内部实现使用
    int n;  // 数组长度
    vector<int> f;  // 记忆化：1 表示能划分完，0 表示不能，-1 表示未知
    vector<int> nums;  // 输入数组的副本

    bool dfs(int i) {  // 判断从下标 i 一直到末尾能否被合法划分
        if (i >= n) {  // 已经越过末尾，说明前面的切分刚好覆盖整个数组
            return true;  // 成功走到终点，返回 true
        }  // if 分支结束
        if (f[i] != -1) {  // 这个状态算过了，直接取缓存，避免重复搜索
            return f[i] == 1;  // 1 → true，0 → false
        }  // if 分支结束
        bool a = i + 1 < n && nums[i] == nums[i + 1];  // 情形一：i 与 i+1 两个数相同，可切成长度 2 的等值段
        bool b = i + 2 < n && nums[i] == nums[i + 1] && nums[i + 1] == nums[i + 2];  // 情形二：从 i 起的三个数全相同，可切成长度 3 的等值段
        bool c = i + 2 < n && nums[i + 1] - nums[i] == 1 && nums[i + 2] - nums[i + 1] == 1;  // 情形三：从 i 起的三个数依次加 1，可切成长度 3 的等差段
        f[i] = ((a && dfs(i + 2)) || ((b || c) && dfs(i + 3))) ? 1 : 0;  // 三种切法任一能走到末尾即可（2 数段跳 2 步，3 数段跳 3 步），结果存成 0/1
        return f[i] == 1;  // 把 0/1 转回 bool 作为本层返回值
    }  // dfs 结束
};  // 类定义结束
