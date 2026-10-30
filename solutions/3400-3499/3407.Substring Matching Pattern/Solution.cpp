// 3407. 子字符串匹配模式 / Substring Matching Pattern
// 核心思路：按 '*' 把模式串切分成若干片段，在 s 中从前往后贪心地依次查找这些片段。
// 复杂度：时间复杂度 O(n*m)，空间复杂度 O(m)，其中 n、m 分别为 s、p 的长度。
class Solution {  // 题解类定义
public:  // 公有接口
    bool hasMatch(string s, string p) {  // 判断 s 能否匹配只含至多一个 '*' 的模式 p
        int i = 0;  // i 记录 s 中已匹配到的位置
        int pos = 0;  // pos 记录本次匹配到的下标
        int start = 0, end;  // start 为当前模式片段起点，end 为 '*' 的下标
        while ((end = p.find("*", start)) != string::npos) {  // 依次取出每个 '*' 之前的非通配片段
            string t = p.substr(start, end - start);  // 截取两个 '*' 之间的片段（可能为空串）
            pos = s.find(t, i);  // 在 s 的 i 之后查找该片段
            if (pos == string::npos) {  // 找不到片段
                return false;  // 无法匹配，返回 false
            }  // 结束失败分支
            i = pos + t.length();  // 匹配位置后移，保证片段按顺序出现
            start = end + 1;  // 模式串扫描位置后移
        }  // 结束片段循环
        string t = p.substr(start);  // 取出最后一个 '*' 之后的片段
        pos = s.find(t, i);  // 在剩余部分中查找该后缀片段
        if (pos == string::npos) {  // 找不到最后一段
            return false;  // 无法匹配
        }  // 结束失败分支
        return true;  // 所有片段按序匹配成功
    }  // 结束 hasMatch
};  // 结束题解类
