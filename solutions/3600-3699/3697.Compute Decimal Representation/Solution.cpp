// 3697. Compute Decimal Representation（3697. 计算十进制表示）
// 核心思路：从低位到高位逐位拆出数字 d，把 d × 当前位权值 10^p 加入答案（跳过数位为 0 的位），最后反转得到从高位到低位的顺序。
// 复杂度：时间 O(log n)（十进制位数），空间 O(log n)。
class Solution {  // 定义题解类
public:  // 公有接口
    vector<int> decimalRepresentation(int n) {  // 主函数：把 n 表示成若干“数位 × 10 的幂”的列表
        vector<int> ans;  // ans 保存每一项（非零数位对应的十进制量）
        long long p = 1;  // p 是当前位的权值，从个位（1）开始，用 long long 防溢出
        while (n > 0) {  // 逐位处理直到 n 为 0
            int v = n % 10;  // 取出最低位数字
            n /= 10;  // 去掉最低位
            if (v != 0) {  // 该位非零才需要计入
                ans.push_back(p * v);  // 把“数位 × 权值”加入答案
            }  // if 分支结束
            p *= 10;  // 权值提升一个数量级
        }  // 循环结束
        reverse(ans.begin(), ans.end());  // 目前低位在前，反转为高位在前
        return ans;  // 返回结果
    }  // 主函数结束
};  // 类定义结束
