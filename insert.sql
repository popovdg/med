insert into patients_view(id, fio, dob) values (1, 'Иванов Иван Иванович', '1953-10-11');
insert into patients_view(id, fio, dob) values (2, 'Петрова Мария Ивановна', '1960-11-10');
insert into patients_view(id, fio, dob) values (3, 'Семёнов Семён Семёнович', '1970-01-15');

insert into studies (patient, type, date) values (1, 'a', '2016-04-05');
insert into studies (patient, type, date) values (1, 'b', '2016-04-05');
insert into studies (patient, type, date) values (2, 'a', '2016-04-05');