program testPL0;

const year      = 1998;
      foo       = -10;
      achar     = 'a';
      ninenum   = '9';

type name = string;

var ch                  : char;
    bdate               : integer;
    i                   : integer;
    line                : array[1..81] of char;
    sfile               : string;
    yesno               : boolean;
    firstname, surname  : name;

procedure times;
    begin
        i := 1;
        writeln('i= ', i);
        i *= 10;
        writeln('i times 10= ', i);
    end

procedure myname;
    begin
        writeln('Please enter your first name: ');
        readln(firstname);
   
        writeln('Please enter your surname: ');
        readln(surname);

        writeln('Please enter your birthdate: ');
        readln(bdate);
   
        writeln;
        writeln(message, ' ', firstname, ' ', surname);
        writeln('I born in', bdate, ',', year);
    end

procedure conditions;
    begin
        if (1<>0) then
            writeln('Not equal working well');
        if (0=0)
            writeln('Equal working well');
        if (2>=1)
            writeln('Bigger or equal than working well');