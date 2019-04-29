if (bdate > 15)
            writeln('My birthdate is after the 15th of the month');
        else if (bdate < 15)
            writeln('My birtdate is before the 15th of the month');
        else
            writeln('My birthdate is at the 15th of the month');
    end

function times ( i : integer ): integer;
    var it : integer;
    begin
        it := 50;
        it += i;
        writeln('i= ', i);
        it -= i;
        writeln('i= ', i);
        it *= i;
        writeln('i= ', i);
        it /= i;
        writeln('i= ', i);
        times := it
    end;

procedure repeatthis;
    var a: integer;
    begin
        a := 10;
        repeat
            writeln('value of a: ', a);
            a := a + 1
        until a = 20;
    end

procedure forloop;
    var a: integer;
    begin
        for a := 10  to 20 do
   
        begin
            writeln('value of a: ', a);
        end;
    end

begin
    myname;

    mathfunc;

    conditions;

    writeln(times(2));

    repeatthis;
    forloop;
end.