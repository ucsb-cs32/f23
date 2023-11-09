#! /usr/bin/env ruby

PRECEDENCE = {
  '=' => 10,

  '+' => 20,
  '-' => 20,

  '*' => 30,
  '/' => 30,
  '%' => 30
}

class Node
  attr_reader :op
  attr_reader :lhs
  attr_reader :rhs

  def initialize(op, lhs, rhs)
    @op  = op
    @lhs = lhs
    @rhs = rhs
  end

  def to_s
    "(#{@lhs} #{@op} #{@rhs})"
  end
end

def is_right_associative?(token)
  token == '='
end

def parse_primary(tokens)
  if tokens.last == '('
    tokens.pop()
    ast = parse(tokens)

    if tokens.last != ')'
      raise 'Not a close paren: ' + tokens.last
    else
      tokens.pop()
      return ast
    end
  end

  if tokens.last.match(/[0-9]+/)
    return tokens.pop()
  end

  raise 'Not a number: ' + tokens.last
end

def parse(tokens, prec = 0)
  lhs = parse_primary(tokens)
  op  = tokens.last

  while PRECEDENCE.key?(op) and PRECEDENCE[op] > prec
    tokens.pop()

    op_prec  = PRECEDENCE[op]
    op_prec -= 1 if is_right_associative?(op)

    rhs = parse(tokens, op_prec)
    lhs = Node.new(op, lhs, rhs)
    op  = tokens.last
  end

  return lhs
end

tokens = $stdin.read().split()
tokens.push('END')
tokens = tokens.reverse()

ast = parse(tokens)

if tokens.last != 'END'
  raise "Extra tokens: #{tokens}"
end

puts ast
