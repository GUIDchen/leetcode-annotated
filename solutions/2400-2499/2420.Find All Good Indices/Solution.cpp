// 题目：2420. 找到所有好下标（Find All Good Indices）
// 核心思路：先预处理 i 左侧非递增段长度 decr 与 i 右侧非递减段长度 incr，再枚举 i 检查二者是否都不小于 k。
// 时间复杂度：O(n)，三趟线性扫描；空间复杂度：O(n)，两个辅助数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> goodIndices(vector<int>& nums, int k) {  // nums：输入数组；k：好下标两侧各需要的元素个数
        int n = nums.size();  // 数组长度
        vector<int> decr(n, 1);  // decr[i]：i 左侧（以 i-1 结尾）的最长非递增段长度，至少含自身故初值 1
        vector<int> incr(n, 1);  // incr[i]：i 右侧（以 i+1 开头）的最长非递减段长度，同理初值 1
        for (int i = 2; i < n; ++i) {  // 判断左侧是否非递增需要两个相邻元素，故从下标 2 开始
            if (nums[i - 1] <= nums[i - 2]) {  // i 左侧相邻的两个元素仍保持非递增
                decr[i] = decr[i - 1] + 1;  // 接上以 i-1 结尾的那一段，长度加一
            }
        }
        for (int i = n - 3; ~i; --i) {  // 从倒数第三个下标倒序扫描，~i 等价于 i >= 0
            if (nums[i + 1] <= nums[i + 2]) {  // i 右侧相邻的两个元素仍保持非递减
                incr[i] = incr[i + 1] + 1;  // 接上以 i+1 开头的那一段，长度加一
            }
        }
        vector<int> ans;  // 收集所有好下标
        for (int i = k; i < n - k; ++i) {  // 左右各需 k 个元素，所以 i 的取值范围是 [k, n-k)
            if (decr[i] >= k && incr[i] >= k) {  // 左 k 个非递增且右 k 个非递减
                ans.push_back(i);  // 该下标满足题意，加入答案
            }
        }
        return ans;  // 返回升序的好下标列表
    }
};