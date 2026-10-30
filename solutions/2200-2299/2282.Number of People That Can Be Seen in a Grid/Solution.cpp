// 题目：2282. 在一个网格中可以看到的人数（Number of People That Can Be Seen in a Grid）
// 核心思路：行列分别处理，用单调递减栈从右往左维护尚未被挡住的身高，一次扫描数出每个位置向右/向下的可见人数。
// 时间复杂度：O(mn)，每行每列各扫一次且每个元素最多进出栈一次；空间复杂度：O(mn)，答案矩阵与临时列数组均与网格同阶。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<vector<int>> seePeople(vector<vector<int>>& heights) {  // heights：网格中每个格子上的人的身高
        int m = heights.size(), n = heights[0].size();  // 网格的行数与列数
        auto f = [](vector<int>& nums) {  // 局部 lambda：把一条一维序列当作一「排」，返回每个位置能看见的人数
            int n = nums.size();  // 这一排的长度
            vector<int> ans(n);  // 这一排每个位置的可见人数，初始全为 0
            stack<int> stk;  // 单调递减栈：保存从右往左扫描时还没被完全遮住的身高
            for (int i = n - 1; ~i; --i) {  // 从右往左扫描，~i 即 i != -1 的简写，用作循环条件
                while (stk.size() && stk.top() < nums[i]) {  // 栈顶比当前身高矮，这个人一定看得见
                    ++ans[i];  // 每弹出一个更矮的人，就给当前位置记一次可见
                    stk.pop();  // 更矮的人被当前身高完全挡住，左侧的人再也看不到他
                }  // 弹出更矮者的循环结束
                if (stk.size()) {  // 矮的都弹完了，此时栈顶是最近的、不低于自己且未被遮挡的人
                    ++ans[i];  // 这一个人也一定能看见
                }  // 条件判断结束
                while (stk.size() && stk.top() == nums[i]) {  // 身高相同的人会相互遮挡，只应计一次
                    stk.pop();  // 弹出相等身高，避免同一个人被重复统计
                }  // 去重循环结束
                stk.push(nums[i]);  // 当前身高入栈，继续阻挡随后从左边看过来的人
            }  // 扫描结束
            return ans;  // 返回这一排每个位置单独方向上的可见人数
        };  // lambda 结束
        vector<vector<int>> ans;  // 最终答案矩阵，先按行填入
        for (auto& row : heights) {  // 先按行统计，每行向右能看见的人数
            ans.push_back(f(row));  // 每行调用一次 f，得到该行所有列的可见人数
        }  // 行方向统计结束
        for (int j = 0; j < n; ++j) {  // 再按列统计，每列向下能看见的人数
            vector<int> col;  // 暂存第 j 列的身高
            for (int i = 0; i < m; ++i) {  // 从上到下遍历这一列
                col.push_back(heights[i][j]);  // 把该列的一维序列拼出来
            }  // 列内循环结束
            vector<int> add = f(col);  // 复用同一个 f 求这一列每个位置向下的可见人数
            for (int i = 0; i < m; ++i) {  // 把列方向的可见人数合并进答案
                ans[i][j] += add[i];  // 行方向的计数加上列方向的计数就是该格的总可见人数
            }  // 合并循环结束
        }  // 列方向统计结束
        return ans;  // 返回行列两个方向累加后的最终答案
    }  // 方法结束
};  // 类定义结束