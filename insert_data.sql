with patient as
(
	insert into patients(fio, dob) values ('Иванов Иван Иванович', '1953-10-11')
	returning id
),
study1 as (insert into studies (patient, type) select id, 'a' from patient),
study2 as (insert into studies (patient, type) select id, 'b' from patient)
insert into studies (patient, type, date) select id, 'a', '2015-05-05' from patient;


with patient as
(
	insert into patients(fio, dob) values ('Иванова Мария Ивановна', '1960-11-11')
	returning id
),
study as (insert into studies (patient, type) select id, 'a' from patient)
insert into studies (patient, type) select id, 'c' from patient;

insert into patients(fio, dob) values ('Сидоров Иван Петрович', '1953-10-11')