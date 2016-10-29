create table if not exists patients
(
	id serial check(id != 0) primary key,
	fio character varying not null,
	dob date not null,
	sex boolean,
	weight int,
	unique (fio, dob)
);
create or replace view patients_view as select *, date_part('year', age(dob)) as age from patients;

comment on column patients.id is 'Идентификатор пациента';
comment on column patients.fio is 'Фамилмия Имя Отчество';
comment on column patients.dob is 'Дата рождения';
comment on column patients.sex is 'Пол (true - мужской, false - женский)';
comment on column patients.weight is 'Вес';

create table if not exists studies
(
	patient int not null references patients (id) match simple on update cascade on delete cascade,
	type character varying not null,
	date date not null,
	unique(patient, type, date)
);
create index on studies (patient);

comment on column studies.date is 'Дата исследования';
comment on column studies.type is 'Тип исследования';
comment on column studies.patient is 'Идентификатор пациента'
