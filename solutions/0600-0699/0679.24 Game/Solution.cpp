// 题目：679. 24 点游戏（24 Game）
// 思路：从当前数字集合里任取两个数做 + - * /，把结果放回后继续递归；只剩一个数时判断它是否等于 24。
// 时间复杂度：O(1)（牌数固定为 4，搜索状态数是常数级）；空间复杂度：O(1)，递归深度与临时向量长度都以 4 为界。
class Solution {  // LeetCode 约定的题解类
public:  // 对外暴露的解法入口
    bool judgePoint24(vector<int>& cards) {  // cards：四张牌的点数
        vector<double> nums;  // 统一用浮点数保存，避免整数除法丢掉小数部分
        for (int num : cards) {  // 逐张牌处理
            nums.push_back(static_cast<double>(num));  // 显式转换成 double 后放入 nums
        }
        return dfs(nums);  // 从四张牌的初始状态开始搜索
    }

private:  // 以下为内部辅助成员
    const char ops[4] = {'+', '-', '*', '/'};  // 四种可用运算符

    bool dfs(vector<double>& nums) {  // nums：当前还剩下的所有数字
        int n = nums.size();  // 当前剩余数字的个数
        if (n == 1) {  // 只剩一个数，到达递归出口
            return abs(nums[0] - 24) < 1e-6;  // 用浮点误差容忍判断它是否等于 24
        }
        bool ok = false;  // 记录本层是否已经找到一组可行解
        for (int i = 0; i < n; ++i) {  // 枚举第一个操作数的下标
            for (int j = 0; j < n; ++j) {  // 枚举第二个操作数的下标（有序枚举，减法和除法不满足交换律）
                if (i != j) {  // 必须是两张不同的牌
                    vector<double> nxt;  // 存放「其余数字 + 本次运算结果」的新集合
                    for (int k = 0; k < n; ++k) {  // 把没被选中的数字搬到 nxt 中
                        if (k != i && k != j) {  // 跳过本次参与运算的两个数
                            nxt.push_back(nums[k]);  // 保留剩下的数字
                        }
                    }
                    for (char op : ops) {  // 依次尝试四种运算符
                        switch (op) {  // 按运算符选择对应的运算
                        case '/':  // 除法分支
                            if (nums[j] == 0) {  // 除数不能为 0
                                continue;  // 直接跳过这次除法
                            }
                            nxt.push_back(nums[i] / nums[j]);  // 把商加入新集合
                            break;  // 结束除法分支
                        case '*':  // 乘法分支
                            nxt.push_back(nums[i] * nums[j]);  // 把积加入新集合
                            break;  // 结束乘法分支
                        case '+':  // 加法分支
                            nxt.push_back(nums[i] + nums[j]);  // 把和加入新集合
                            break;  // 结束加法分支
                        case '-':  // 减法分支
                            nxt.push_back(nums[i] - nums[j]);  // 把差加入新集合（顺序不能交换）
                            break;  // 结束减法分支
                        }
                        ok |= dfs(nxt);  // 对新集合递归搜索；|= 保证已有的成功结果不会被覆盖
                        if (ok) {  // 已经找到解，无需继续搜索
                            return true;  // 向上层报告成功
                        }
                        nxt.pop_back();  // 回溯：弹出本次运算结果，恢复 nxt 供下一个运算符使用
                    }
                }
            }
        }
        return ok;  // 所有分支都失败，返回本层结果
    }
};