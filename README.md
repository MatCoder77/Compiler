# Compiler
## About
Compiler for a simple imperative language written in C++. Source code is compiled to machine code which can be executed by register machine attached to this project.

## Requirements
- Flex 2.6.4
- Bison 3.0.4
- g++
- GNU Make

The project was compiled and tested under Ubuntu 18. 
C++17 or higher is recommended.

## Usage
The project can be build using `make` command. To compile source code  contained in file 'source.imp' to file 'destination.mr' with machine code, use the following command:
'/kompilator source.imp destination.mr'

## Executing compiled programs
Compiled code can be executed on a register machine added to this project. A detailed description of running compiled programs can be found in `register-machine` folder.

## Language Specification
Language accepted by the compiler is described with the following grammar:


    program      -> DECLARE declarations IN commands END

    declarations -> declarations pidentifier;
                | declarations pidentifier(num:num);
                | 

    commands     -> commands command
                | command

    command      -> identifier := expression;
                | IF condition THEN commands ELSE commands ENDIF
                | IF condition THEN commands ENDIF
                | WHILE condition DO commands ENDWHILE
                | DO commands WHILE condition ENDDO
                | FOR pidentifier FROM value TO value DO commands ENDFOR
                | FOR pidentifier FROM value DOWNTO value DO commands ENDFOR
                | READ identifier;
                | WRITE value;

    expression   -> value
                | value + value
                | value - value
                | value * value
                | value / value
                | value % value

    condition    -> value = value
                | value != value
                | value < value
                | value > value
                | value <= value
                | value >= value

    value        -> num
                | identifier

    identifier   -> pidentifier
                | pidentifier(pidentifier)
                | pidentifier(num)

## Example program
Simple program written in language accepted by compiler:

Poniżej znajduje się przykładowy program napisany w tym języku:

    [ Factorization ]
    DECLARE
        n; m; reszta; potega; dzielnik;
    IN
        READ n;
        dzielnik := 2;
        m := dzielnik * dzielnik;
        WHILE n >= m DO
            potega := 0;
            reszta := n % dzielnik;
            WHILE reszta = 0 DO
                n := n / dzielnik;
                potega := potega + 1;
                reszta := n % dzielnik;
            ENDWHILE
            IF potega > 0 THEN [ czy znaleziono dzielnik ]
                WRITE dzielnik;
                WRITE potega;
            ELSE
                dzielnik := dzielnik + 1;
                m := dzielnik * dzielnik;
            ENDIF
        ENDWHILE
        IF n != 1 THEN [ ostatni dzielnik ]
            WRITE n;
            WRITE 1;
        ENDIF
    END
