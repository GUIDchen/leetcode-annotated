// 题目：420. 强密码检验器（Strong Password Checker）
// 思路：按长度分三段——太短（<6）插入/替换取较大值；长度合法只需替换重复段并补字符种类；太长（>20）先利用重复段长度模 3 的余数高效删除，再用删 2/删 3 的方式抵扣替换。
// 时间复杂度：O(n)，只常数遍扫描；空间复杂度：O(1)，只用几个计数变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int strongPasswordChecker(string password) {  // password 是待检测的密码，返回使密码变强所需的最少操作次数
        int types = countTypes(password);  // types 统计出现了几类字符（小写/大写/数字）
        int n = password.size();  // n 是密码长度
        if (n < 6) return max(6 - n, 3 - types);  // 太短（长度 < 6）：插入和替换都能顺带补字符种类，取两者所需次数的较大值
        if (n <= 20) {  // 长度合法（6 ~ 20）：只需考虑替换重复字符与补足字符种类
            int replace = 0, cnt = 0;  // replace 记录替换次数，cnt 记录当前连续相同字符的个数
            char prev = '~';  // prev 初始为不可能出现的字符，保证第一轮进入 else 分支
            for (char& curr : password) {  // 逐字符扫描
                if (curr == prev)  // 与前一字符相同，连续长度加一
                    ++cnt;  // 连续计数 +1
                else {  // 否则一段连续相同字符结束
                    replace += cnt / 3;  // 长度 k 的连续段需要 k/3 次替换才能消除所有三连
                    cnt = 1;  // 新的一段从当前字符开始计数
                    prev = curr;  // 更新 prev 为当前字符
                }  // if-else 结束
            }  // 循环结束
            replace += cnt / 3;  // 收尾：最后一段也要累加 k/3 次替换
            return max(replace, 3 - types);  // 替换与补种类可以合并进行，取较大值
        }  // 长度合法分支结束
        int replace = 0, remove = n - 20;  // 太长（长度 > 20）：remove 是必须删掉的字符数
        int remove2 = 0;  // remove2 记录「长度 % 3 == 1 的重复段」个数，之后删 2 个字符可省一次替换
        int cnt = 0;  // cnt 记录当前连续相同字符的个数
        char prev = '~';  // prev 初始为哨兵字符
        for (char& curr : password) {  // 逐字符扫描，切分出每一段连续相同字符
            if (curr == prev)  // 连续长度加一
                ++cnt;  // 连续计数 +1
            else {  // 一段连续相同字符结束
                if (remove > 0 && cnt >= 3) {  // 还有删除额度，且这一段长度 >= 3
                    if (cnt % 3 == 0) {  // 长度是 3 的倍数：删掉 1 个字符就能减少一次替换需求
                        --remove;  // 消耗一个删除额度
                        --replace;  // 对应地替换需求减一
                    } else if (cnt % 3 == 1)  // 长度 % 3 == 1：先记下来，后面删 2 个字符也能省一次替换
                        ++remove2;  // 这类重复段计数加一
                }  // 模 3 余数判断结束
                replace += cnt / 3;  // 仍然按长度 / 3 累加需要的替换次数
                cnt = 1;  // 重置当前段计数
                prev = curr;  // 更新 prev
            }  // 段结束分支结束
        }  // 循环结束
        if (remove > 0 && cnt >= 3) {  // 收尾处理最后一段（逻辑与循环内完全相同）
            if (cnt % 3 == 0) {  // 最后一段长度是 3 的倍数
                --remove;  // 删掉一个字符
                --replace;  // 替换需求减一
            } else if (cnt % 3 == 1)  // 最后一段长度 % 3 == 1
                ++remove2;  // 计入 remove2
        }  // 收尾分支结束
        replace += cnt / 3;  // 累加最后一段需要的替换次数

        int use2 = min(min(replace, remove2), remove / 2);  // 用「删 2 个字符」的方式一次性消掉一个替换需求，取三者最小
        replace -= use2;  // 替换需求相应减少
        remove -= use2 * 2;  // 消耗 2 倍的删除额度

        int use3 = min(replace, remove / 3);  // 剩下的替换需求用「删 3 个字符」来解决
        replace -= use3;  // 替换需求减少
        remove -= use3 * 3;  // 消耗 3 倍的删除额度
        return (n - 20) + max(replace, 3 - types);  // 总操作数 = 必删的 (n - 20) 次 + 剩余替换与补种类的较大值
    }  // strongPasswordChecker 方法结束

    int countTypes(string& s) {  // 统计密码中出现了几类字符：小写、大写、数字
        int a = 0, b = 0, c = 0;  // a/b/c 分别标记是否出现小写、大写、数字
        for (char& ch : s) {  // 逐字符检查
            if (islower(ch))  // 出现小写字母
                a = 1;  // 标记小写
            else if (isupper(ch))  // 出现大写字母
                b = 1;  // 标记大写
            else if (isdigit(ch))  // 出现数字
                c = 1;  // 标记数字
        }  // 循环结束
        return a + b + c;  // 返回出现的字符种类数（0 ~ 3）
    }  // countTypes 方法结束
};  // Solution 类结束