// 题目：398. 随机数索引（Random Pick Index）
// 思路：蓄水池抽样。顺序扫描数组，遇到第 n 个等于 target 的位置时以 1/n 的概率把它选为答案，从而每个合法下标被选中的概率都相等。
// 时间复杂度：O(n)，每次 pick 只扫一遍数组；空间复杂度：O(1)，除保存数组外只用了几个计数变量。
class Solution {  // LeetCode 约定的题解类
public:  // 构造函数与 pick 方法对外可见
    vector<int> nums;  // 成员变量：保存输入数组，供多次 pick 调用复用

    Solution(vector<int>& nums) {  // 构造函数：接收原始数组，引用传参避免拷贝
        this->nums = nums;  // 用 this 区分同名的成员变量与形参，把数组存进对象
    }

    int pick(int target) {  // 随机返回 target 在数组中出现的某一个下标，要求等概率
        int n = 0, ans = 0;  // n 记录已遇到的 target 个数；ans 保存当前被抽中的下标
        for (int i = 0; i < nums.size(); ++i) {  // 顺序扫描整个数组
            if (nums[i] == target) {  // 只处理值等于 target 的位置
                ++n;  // 第 n 次遇到 target，计数器加一
                int x = 1 + rand() % n;  // 在 [1, n] 中均匀随机取一个整数，相当于一次抽签
                if (n == x) ans = i;  // 抽到 n 的概率恰为 1/n，此时替换答案，保证每个位置等概率
            }
        }
        return ans;  // 返回最终选中的下标
    }  // pick 方法结束
};  // 题解类结束

// 下面是 LeetCode 给出的调用示例（判题器代码，无需实现）：
/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(nums);
 * int param_1 = obj->pick(target);
 */