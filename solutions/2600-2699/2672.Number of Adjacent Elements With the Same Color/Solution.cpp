// 题目：2672. 有相同颜色的相邻元素数目（Number of Adjacent Elements With the Same Color）
// 思路：维护颜色数组 nums 和当前相邻同色对数 x；每次改色只影响 i 与左右邻居，先减掉旧的同色对再补上新的。
// 时间复杂度：O(n + q)，每个查询 O(1)；空间复杂度：O(n)，需要保存颜色数组与答案数组。
class Solution {  // 逐次涂色，并实时维护「相邻同色对数」
public:  // 对外接口
    vector<int> colorTheArray(int n, vector<vector<int>>& queries) {  // n 个位置初始都未涂色，queries 的每项是 [下标, 颜色]
        vector<int> nums(n);  // nums[i] 表示位置 i 当前的颜色，0 表示还没被涂过
        vector<int> ans;  // 记录每次涂色完成后的相邻同色对数
        int x = 0;  // x 就是当前的相邻同色对数
        for (auto& q : queries) {  // 依次处理每一次涂色操作
            int i = q[0], c = q[1];  // i 是本次涂色的位置，c 是要涂的新颜色
            if (i > 0 && nums[i] > 0 && nums[i - 1] == nums[i]) {  // 情况一：i 原来已涂色且与左邻居同色，这一对会被本次改色拆掉
                --x;  // 减去左边这一对
            }  // if 结束
            if (i < n - 1 && nums[i] > 0 && nums[i + 1] == nums[i]) {  // 情况二：i 原来已涂色且与右邻居同色，同样会被拆掉
                --x;  // 减去右边这一对
            }  // if 结束
            if (i > 0 && nums[i - 1] == c) {  // 情况三：改色后 i 与左邻居同色，新增一对
                ++x;  // 加上左边这一对新贡献
            }  // if 结束
            if (i < n - 1 && nums[i + 1] == c) {  // 情况四：改色后 i 与右邻居同色，新增一对
                ++x;  // 加上右边这一对新贡献
            }  // if 结束
            ans.push_back(x);  // 本次涂色完成后把当前答案记入结果
            nums[i] = c;  // 最后才写入新颜色，保证上面四次判断用的都是旧颜色
        }  // 一次查询处理结束
        return ans;  // 返回每次涂色后的相邻同色对数
    }  // colorTheArray 结束
};  // 类定义结束