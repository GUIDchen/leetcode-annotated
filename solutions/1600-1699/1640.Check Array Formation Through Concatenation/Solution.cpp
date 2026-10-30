// 题目：1640. 能否连接形成数组（Check Array Formation Through Concatenation）
// 思路：指针 i 顺序扫描 arr，每步在 pieces 里找首元素等于 arr[i] 的碎片，再逐元素核对整段碎片是否与 arr 后段一致，全部对上就前进。
// 时间复杂度：O(n·m)，n 为 arr 长度、m 为 pieces 中碎片个数；空间复杂度：O(1)，只用常数个下标变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外开放
    bool canFormArray(vector<int>& arr, vector<vector<int>>& pieces) {  // arr：目标数组；pieces：碎片数组，判断能否用每个碎片整体拼出 arr
        for (int i = 0; i < arr.size();) {  // i 指向 arr 中下一个尚未被消费的元素，自增放在内层 while 里
            int k = 0;  // k 记录「首元素等于 arr[i]」的碎片下标
            while (k < pieces.size() && pieces[k][0] != arr[i]) {  // 逐个碎片比较它的第一个元素与 arr[i]
                ++k;  // 首元素对不上就换下一个碎片
            }  // 找碎片的循环结束
            if (k == pieces.size()) {  // 所有碎片的首元素都对不上，说明 arr[i] 无处安放
                return false;  // 拼接失败，立即返回 false
            }  // 失败分支结束
            int j = 0;  // j 是碎片 k 内部的下标，从碎片开头开始核对
            while (j < pieces[k].size() && arr[i] == pieces[k][j]) {  // 整段碎片必须与 arr 的对应片段逐元素相等
                ++i;  // arr 的消费位置后移
                ++j;  // 碎片内部下标后移
            }  // 比对循环结束，此时碎片 k 已全部匹配
        }  // 继续处理 arr 中剩余的元素
        return true;  // arr 被完整消费，说明可以拼接形成
    }  // 方法结束
};  // 类定义结束