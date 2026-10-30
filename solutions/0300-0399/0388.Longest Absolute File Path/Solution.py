# 题目：388. 文件的最长绝对路径（Longest Absolute File Path）
# 思路：用列表当栈按下标保存每层目录的累计绝对路径长度，按行扫描：先数制表符得到深度，再弹栈、取父路径长度、目录入栈。
# 时间复杂度：O(n)，每个字符只被扫描常数次；空间复杂度：O(n)，栈最多保存最大嵌套深度的目录长度。
class Solution:  # 题解类
    def lengthLongestPath(self, input: str) -> int:  # input 是用换行分行、制表符表示目录层级的文件系统字符串
        i, n = 0, len(input)  # i 是扫描下标，n 是字符串总长度
        ans = 0  # ans 保存已见过的最长文件绝对路径长度
        stk = []  # 当栈用：下标 k 处的值表示深度为 k 的目录的累计路径长度
        while i < n:  # 按行（以换行符分隔）逐行扫描输入
            ident = 0  # ident 记录本行开头的制表符个数，也就是目录深度
            while input[i] == '\t':  # 连续吃掉行首的所有制表符
                ident += 1  # 每多一个制表符，就多嵌套一层
                i += 1  # 下标前进，继续看下一个字符

            cur, isFile = 0, False  # cur 统计本行条目本身的长度，isFile 标记它是不是文件
            while i < n and input[i] != '\n':  # 一直扫到本行结尾的换行符为止
                cur += 1  # 名字长度加一
                if input[i] == '.':  # 名字里出现点号，说明这一行是文件
                    isFile = True  # 置上文件标记
                i += 1  # 继续扫描本行剩余字符
            i += 1  # 跳过本行结尾的换行符，指向下一行首字符

            # 弹栈：栈深超过本行深度，说明那些目录已经不在当前路径上了
            # popd
            while len(stk) > 0 and len(stk) > ident:  # 只保留深度小于本行深度的祖先目录
                stk.pop()  # 弹出多余的层级

            if len(stk) > 0:  # 栈不空说明本行不在根目录，前面还有父路径要拼接
                cur += stk[-1] + 1  # 加上父目录的累计长度和连接用的那一个 '/'

            # 入栈：目录要留给子项复用累计长度，文件只更新答案
            # pushd
            if not isFile:  # 目录才需要入栈给下一层用
                stk.append(cur)  # 记录该目录的累计绝对路径长度
                continue  # 目录不参与答案更新，直接处理下一行

            ans = max(ans, cur)  # 本行是文件，用它完整的绝对路径长度更新最大值

        return ans  # 返回最长文件路径长度；输入里没有文件时就是 0
