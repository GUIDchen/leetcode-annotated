// 题目：2449. 使数组相似的最少操作次数（Minimum Number of Operations to Make Arrays Similar）
// 思路：两个数组都按「奇偶性优先、大小其次」排序后分组配对——奇数只与奇数、偶数只与偶数逐位比较，绝对差之和再除以 4。
// 时间复杂度：O(n log n)，瓶颈是两次排序；空间复杂度：O(n)，四个分组数组共保存 n 个元素。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    long long makeSimilar(vector<int>& nums, vector<int>& target) {  // nums：待调整数组；target：目标数组；答案可能超过 int 范围故返回 long long
        sort(nums.begin(), nums.end());  // 把 nums 升序排序，使同奇偶的元素按大小有序，方便同组内逐位配对
        sort(target.begin(), target.end());  // target 同样升序排序，保证与 nums 的分组顺序一致
        vector<int> a1;  // 存放 nums 里的奇数（排序后天然保持升序）
        vector<int> a2;  // 存放 nums 里的偶数（排序后天然保持升序）
        vector<int> b1;  // 存放 target 里的奇数
        vector<int> b2;  // 存放 target 里的偶数
        for (int v : nums) {  // 遍历 nums 的每个元素，按奇偶性分流
            if (v & 1)  // 最低位为 1 说明 v 是奇数
                a1.emplace_back(v);  // 奇数放入 a1 组
            else  // 否则 v 一定是偶数
                a2.emplace_back(v);  // 偶数放入 a2 组
        }
        for (int v : target) {  // 遍历 target 的每个元素，用完全相同的规则分流
            if (v & 1)  // 判断 target 当前元素是否为奇数
                b1.emplace_back(v);  // target 的奇数放入 b1 组
            else  // 否则为偶数
                b2.emplace_back(v);  // target 的偶数放入 b2 组
        }
        long long ans = 0;  // 累计逐位绝对差的总和，用 long long 防止累加溢出
        for (int i = 0; i < a1.size(); ++i) ans += abs(a1[i] - b1[i]);  // 奇数分组内同位置配对，累加两者距离
        for (int i = 0; i < a2.size(); ++i) ans += abs(a2[i] - b2[i]);  // 偶数分组内同位置配对，累加两者距离
        return ans / 4;  // 一次操作同时让一个元素 +2、另一个元素 -2，最多消去 4 点总差，故总差除以 4 就是操作次数
    }
};