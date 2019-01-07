import re
# only reserved characters in the cfg is `.
# ` = non-terminal
# `` = code
# ``` = regular expression (token)
# ```` = comment
# any more ticks in series is illegal for the cfg

# format for a non-terminal will be `<name>` := <expression>|<expression>
def code_eval(tabs, term, data, eval_r):
    curr = ''
    if term in eval_r:
        curr += eval_r[term]
    else:
        curr = '\n'

    return curr

def split_string_escaped(s, delim):
    escape = False
    curr = ''
    lst = []

    for c in s:
        if escape:
            escape = False
            if c == '\\':
                escape = True
            curr += ('\\' + c)
        else:
            if c == '\\':
                escape = True
            else:
                if c == delim:
                    lst += [curr]
                    curr = ''
                else:
                    curr += c
    
    lst += [curr]
    return lst

def cleanup(s):
    curr = ''
    if s[0] == r'^':
        s = s[1:len(s)]
    for c in s:
        if c != '\\':
            curr += c
    
    return curr


def checkValues(d,v,n):
    for i in range(0,n):
        if d[str(i)] == v:
            return True
    
    return False

def first(cfg, term, firsts, toks):
    if term in firsts:
        return firsts[term]
    
    f = []
    exprs = cfg[term]
    for exp in exprs:
        if exp[0][0] != '`':
            if not exp[0] in f:
                f += [exp[0]]
        elif exp[0][1] == '`':
            if not toks[exp[0]] in f:
                f += [toks[exp[0]]]
        else:
            n = first(cfg, exp[0], firsts, toks)
            for t in n:
                if not t in f:
                    f += [t]

    firsts[term] = f
    return f

def code_option(tabs, exp, term, snippets, token_map, tokens, firsts):
    code = ''
    # if tabs is 0, then we are looking at the initial differentiator
    if len(exp) == 0:
        for _ in range(0, tabs):
            code += '\t'
        code += 'Tuple rt;\n'
        for _ in range(0, tabs):
            code += '\t'
        code += 'rt.token = h;\n'
        for _ in range(0, tabs):
            code += '\t'
        code += 'rt.node = r;\n'
        for _ in range(0, tabs):
            code += '\t'
        code += 'return rt;\n'
        return code
    else:
        first_token = exp[0]
        if first_token[0] != '`' or (first_token[0] == '`' and first_token[1] == '`'):
            for _ in range(0, tabs):
                code += '\t'
            # we are looking at an explicit or a implied token
            if first_token[0] != '`':
                code += 'if(lookahead(h) == ' + str(token_map.index(first_token)) + ') {\n'
            else:
                code += 'if(lookahead(h) == ' + str(token_map.index(tokens[first_token])) + ') {\n'
            
            tabs += 1
            for _ in range(0, tabs):
                code += '\t'
            code += snippets[5]
            for _ in range(0, tabs):
                code += '\t'
            code += snippets[6]
            for _ in range(0, tabs):
                code += '\t'
            code += snippets[7]
            for _ in range(0, tabs):
                code += '\t'
            code += snippets[8]

            for _ in range(0, tabs):
                code += '\t'
            if first_token[0] != '`':
                code += 'h = match_token(h, ' + str(token_map.index(first_token)) + ');\n\n'
            else:
                code += 'h = match_token(h, ' + str(token_map.index(tokens[first_token])) + ');\n\n'
            
            code += code_option(tabs, exp[1:len(exp)], term, snippets, token_map, tokens, firsts)

            tabs -= 1
            for _ in range(0, tabs):
                code += '\t'
            code += '}'
            
            if tabs != 1:
                code += '\n'
        else:
            # we are looking at a parse
            for _ in range(0, tabs):
                code += '\t'
            code += 'if('
            check = 0
            for c in firsts[first_token]:
                code += 'lookahead(h) == ' + str(token_map.index(c))
                if check != len(firsts[first_token]) - 1:
                    code += ' || '
                
                check += 1
            code += ') {\n'

            tabs += 1
            
            for _ in range(0, tabs):
                code += '\t'
            code += 'Tuple t = parse_' + first_token[1:-1] + '(h);\n'

            for _ in range(0, tabs):
                code += '\t'
            code += snippets[9]
            for _ in range(0, tabs):
                code += '\t'
            code += snippets[10]
            for _ in range(0, tabs):
                code += '\t'
            code += snippets[11]
            for _ in range(0, tabs):
                code += '\t'
            code += snippets[12]

            code += code_option(tabs, exp[1:len(exp)], term, snippets, token_map, tokens, firsts)
            tabs -= 1
            
            for _ in range(0, tabs):
                code += '\t'
            code += '}'

            if tabs != 1:
                code += '\n'

        return code

def code_f(cfg, firsts, tokens, snippets, l, term):
    # l is list that is written to the tokenizer. without regex
    code = ''

    code += '\t' + snippets[0]
    code += '\t' + snippets[1]
    code += '\t' + snippets[2]
    code += '\t' + snippets[3]
    code += '\t' + snippets[4]
    code += '\t' + 'r->name = (char*)malloc(' + str(len(term[1:-1])) + ' * sizeof(char));\n'
    code += '\t' + 's_move(r->name, "' + term[1:-1] + '");\n\n'

    shortest_expr = len(cfg[term][0])
    for exp in cfg[term]:
        if len(exp) < shortest_expr:
            shortest_expr = len(exp)

    longest_expr = -1
    for exp in cfg[term]:
        if len(exp) > longest_expr:
            longest_expr = len(exp)

    cutoff = 0

    for i in range(0, shortest_expr):
        name = cfg[term][0][i]
        double = False
        for exp in cfg[term]:
            if (exp[i][0] == '`') and (exp[i][1] != '`'):
                if name != exp[i]:
                    double = True
                    break
            else:
                double = True
                break
            
        if double:
            break
        
        cutoff += 1

    for i in range(0, cutoff):
        code += '\t' + 'Tuple t = parse_' + cfg[term][0][i][1:-1] + '(h);\n'
        code += '\t' + snippets[9]
        code += '\t' + snippets[10]
        code += '\t' + snippets[11]
        code += '\t' + snippets[12]

    count = 0
    code += '\n'
    for exp in cfg[term]:
        count += 1
        if cutoff != len(exp):
            code += code_option(1, exp[cutoff:len(exp)], term, snippets, l, tokens, firsts)
        if count != len(cfg[term]):
            yes = False
            for i in range(count, len(cfg[term])):
                if cutoff != len(cfg[term][i]):
                    yes = True
                    break
            if yes:
                code += ' else '
        if count == len(cfg[term]) and cutoff != 0:
            if longest_expr != 1:
                code += ' else {\n'
                code += '\t\tTuple rt;\n'
                code += '\t\trt.token = h;\n'
                code += '\t\trt.node = r;\n'
                code += '\t\treturn rt;\n'
                code += '\t}\n'
            else:
                code += '\tTuple rt;\n'
                code += '\trt.token = h;\n'
                code += '\trt.node = r;\n'
                code += '\treturn rt;\n'
    code += '\n\tprintf("Parse Error: Token -> %s\\n", h->value);\n\texit(0);\n}\n'
    return code

class CFG:
    def __init__(self):
        # self.cfg is a dictionary of non-terminals -> expressions
        # expression should take the form of a tuple (``` or `, ``)
        self.cfg = {}

        # self.tokens will take the form of a ``` to a regex
        self.tokens = {}

        # self.firsts will take the form of a `` to a []
        self.firsts = {}
        self.first_instruction = ''

        self.eval = {}

        self.data = ''
        self.data2 = ''
        self.data3 = []

    def load(self, filename):
        fp = open(filename, 'r')
        line_n = 0
        referenced_terminals = []
        referenced_tokens = []
        tok_n = 0
        getting_data = False
        collecting_code = None
        curr_code = ''

        for line in fp:
            line_n += 1
            a = re.match(r'^(```[a-zA-Z]+```)\s*->\s*(.*)$', line)
            b = re.match(r'^(`[a-zA-Z]+`)\s*->\s*(.*)$', line)
            c = re.match(r'^`````$', line)
            d = re.match(r'^`!`\s*->\s*(.*)$', line)
            e = re.match(r'^`(`[a-zA-Z]+`)`\s*->\s*{$', line)
            f = re.match(r'^}$', line)

            if collecting_code:
                if not f:
                    curr_code += '\t' + line
                else:
                    self.eval[collecting_code] = curr_code
                    curr_code = ''
                    collecting_code = None

                continue

            if getting_data:
                if not line == '`````':
                    self.data += '\t' + line
                    in_white = -1
                    util = ''
                    for c in line:
                        if in_white == -1:
                            if c != ' ' and c != '\t' and c != '\r' and c != '*' and c != '\n':
                                in_white = 0
                            continue
                        if in_white == 1:
                            if c != ' ' and c != '\t' and c != '\r' and c != '*' and c != '\n':
                                in_white = 2
                                util += c
                            continue
                        if in_white == 0:
                            if c == ' ' or c == '\t' or c == '\r' or c == '*' or c == '\n':
                                in_white = 1
                            continue
                        if in_white == 2:
                            if c != ' ' and c != '\t' and c != '*':
                                if c != ';' and c != '\n' and c != '\r':
                                    util += c
                            else:
                                util = ''
                                in_white = 1
                            continue
                    self.data3 += [util]
                    self.data2 += '\t\t' + 'n->' + util + ' = d->' + util + ';\n'
                else:
                    getting_data = False
                continue
            
            if d:
                # first instruction:
                self.first_instruction = d.group(1)
            elif e:
                collecting_code = e.group(1)
            elif f:
                if collecting_code != None:
                    self.eval[collecting_code] = curr_code
                    curr_code = ''
                    collecting_code = None
            elif a:
                # we are looking at a token definitions, group 1 is token name, group 2 is regex
                if a.group(1) in self.tokens:
                    raise ValueError(str(line_n) + ': Repeat definition of token.')
                
                r = a.group(2)
                start = 0
                end = len(r)

                if r[0] == r'^':
                    start = 1
                if r[len(r) - 1] == r'$':
                    end = len(r) - 1

                # TODO: CHECK IF TOKEN REGEX IS A VALID REGEX #
                self.tokens[a.group(1)] = r'^' + r[start:end]
            elif b:
                # we are looking at a non-terminal definition. group 1 is non-terminal name
                # group 2 is string representation of non-terminal result
                t = b.group(1)
                if t in self.cfg:
                    raise ValueError(str(line_n) + ': non-terminal redeclatation.')

                self.cfg[t] = []
                exps = b.group(2)
                exps = split_string_escaped(exps, '|')
                
                for exp in exps:
                    # we want to extract each token and note the discovered tokens and terminals
                    mode = 0
                    curr_mode = 0
                    in_type = False
                    counting_down = False
                    curr = ''
                    # mode = 1 -> terminal, mode = 2 -> code, mode = 3 -> token, mode = 4 -> comment

                    tokenized = []

                    for c in exp:
                        if c != ' ' and c != '\t' and c != '\n' and c != '\r':
                            if c == '`' and not in_type:
                                in_type = True

                                if curr != '' and curr != '`':
                                    # this is a token of some sort (curr)
                                    # TODO: Escape regex properly
                                    if not (checkValues(self.tokens, ('^' + curr), tok_n)):
                                        self.tokens[str(tok_n)] = r'^' + curr
                                        tok_n += 1
                                    tokenized += [curr]
                                    curr = ''

                            if c != '`' and in_type:
                                counting_down = True

                            if in_type and c == '`' and not counting_down:
                                mode += 1
                                curr_mode = mode

                            if in_type and c == '`' and counting_down:
                                mode -= 1
                            
                            if mode == 0 and counting_down:
                                counting_down = False
                                in_type = False

                                if curr != '':
                                    # this is either code, a non-terminal, a token, or a comment
                                    curr += c
                                    if curr_mode == 1:
                                        referenced_terminals += [curr]
                                    elif curr_mode == 3:
                                        referenced_tokens += [curr]
                                    tokenized += [curr]
                                    curr = ''

                            curr += c
                        else:
                            if curr != '' and curr != '`':
                                # this is a token of some sort (curr)
                                # TODO: Escape regex properly
                                if not (checkValues(self.tokens, ('^' + curr), tok_n)):
                                    self.tokens[str(tok_n)] = r'^' + curr
                                    tok_n += 1
                                tokenized += [curr]
                                curr = ''

                            mode = 0
                            curr_mode = 0
                            in_type = False
                            counting_down = False
                            curr = ''

                    if curr != '' and curr != '`':
                        # this is a token of some sort (curr)
                        # TODO: Escape regex properly
                        if not (checkValues(self.tokens, ('^' + curr), tok_n)):
                            self.tokens[str(tok_n)] = r'^' + curr
                            tok_n += 1
                        tokenized += [curr]
                        curr = ''

                    self.cfg[t] += [tokenized]
            elif c:
                if not getting_data:
                    getting_data = True
                    self.data = ''

        # print(self.tokens)
        # print(self.cfg)
        for tok in referenced_tokens:
            if not (tok in self.tokens):
                raise ValueError('Missing token definition for ' + tok + '.')

        for term in referenced_terminals:
            if not (term in self.cfg):
                raise ValueError('Missing terminal definition for ' + term + '.')

        d = {}
        l = []
        for i in range(0, tok_n):
            tok = self.tokens[str(i)]
            n_tok = cleanup(tok)
            d[n_tok] = tok
            l += [n_tok]

        l.sort(key=len, reverse=True)
        for i in range(0, tok_n):
            self.tokens[str(i)] = d[l[i]]
        
        # print(self.tokens)
        # print(self.cfg)

        # now we are prepared to write the tokens to the C tokenizer:
        n = open('destination/tokenize.c', 'w')
        fp = open('target/tokenize.c', 'r')

        line_number = 0
        for line in fp:
            line_number += 1
            if line_number == 34:
                s = '\tchar *all_tokens[' + str(len(self.tokens)) + '] = {'
                for i in range(0, tok_n):
                    s += '"' + d[l[i]] + '"'
                    if i != len(self.tokens) - 1:
                        s += ', '

                for k in self.tokens:
                    if re.match(r'^```[a-zA-Z]+```$', k):
                        l += [self.tokens[k]]
                        d[l[tok_n]] = self.tokens[k]
                        s += '"' + self.tokens[k] + '"'
                        if tok_n != len(self.tokens) - 1:
                            s += ', '
                        
                        tok_n += 1
                
                s += '};\n'
                n.write(s)
            elif line_number == 35:
                n.write('\tint num_toks = ' + str(len(self.tokens)) + ';\n')
            else:
                n.write(line)

        # now we have created the tokenizer, the next step is to create the parser.
        # first thing in writing the parser is we have to write all of the nessesary data types
        n = open('destination/parse.h', 'w')
        fp = open('target/parse.h', 'r')

        line_number = 0
        for line in fp:
            line_number += 1
            if line_number == 22:
                for term in self.cfg:
                    n.write('Tuple parse_' + term[1:-1] + '(Token *h);\n')
            else:
                n.write(line)

        # now we need to calculate the first() for each non-terminal
        for term in self.cfg:
            print(term + ' -> ' + str(first(self.cfg, term, self.firsts, self.tokens)) + '\n')

        n = open('destination/parse.c', 'w')
        fp = open('target/parse.c', 'r')

        line_number = 0
        for line in fp:
            line_number += 1
            if line_number == 20:
                n.write('\treturn parse_clean(parse_' + self.first_instruction + '(h).node);\n')
            elif line_number < 47:
                n.write(line)


        w = open('target/parse_snippets')
        snippets = []
        for line in w:
            snippets += [line]

        for i in range(0, len(l)):
            if d[l[i]] != l[i]:
                l[i] = d[l[i]][1:len(d[l[i]])]

        print(l)
        for term in self.cfg:
            n.write('Tuple parse_' + term[1:-1] + '(Token *h) {\n')
            n.write(code_f(self.cfg, self.firsts, self.tokens, snippets, l, term))
            n.write('\n')

        n = open('destination/evaluate.h', 'w')
        fp = open('target/evaluate.h', 'r')

        line_number = 0
        for line in fp:
            line_number += 1
            if line_number == 8:
                n.write(self.data)
            else:
                n.write(line)

        n = open('destination/evaluate.c', 'w')
        fp = open('target/evaluate.c', 'r')

        line_number = 0
        for line in fp:
            line_number += 1
            if line_number == 9:
                n.write(self.data2)
            elif line.find('void* REPLACEME;') != -1:
                # we need to write the evaluator here:
                i = 0
                for term in self.cfg:
                    curr = ''
                    if i == 0:
                        curr += '\t'
                    curr += 'if(!strcmp(n->name, "' + term[1:-1] + '")) {\n'
                    curr += code_eval(1, term, self.data3, self.eval)
                    if i != len(self.cfg) - 1:
                        curr += '\t} else '
                    else:
                        curr += '\t}\n'
                    n.write(curr)
                    i += 1

            else:
                n.write(line)


CFG().load('tests/language.cfg')
        