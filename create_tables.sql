drop table patients cascade;
create table patients
(
	id serial check (id != 0) primary key,
	fio character varying not null CHECK (fio <> ''),
	dob date not null check (dob <= CURRENT_DATE),
	sex boolean,
	weight int check (weight > 0),
	unique (fio, dob)
);
create or replace view patients_view as select *, date_part('year', age(dob)) as age from patients;

comment on column patients.id is 'Идентификатор пациента';
comment on column patients.fio is 'Фамилмия Имя Отчество';
comment on column patients.dob is 'Дата рождения';
comment on column patients.sex is 'Пол (true - мужской, false - женский)';
comment on column patients.weight is 'Вес';

drop table studies;
create table studies
(
	patient int not null references patients (id) match simple on update cascade on delete cascade,
	type character varying not null CHECK (type <> ''),
	date date not null default CURRENT_DATE check (date <= CURRENT_DATE),
	unique(patient, type, date)
);
create index on studies (patient);

comment on column studies.date is 'Дата исследования';
comment on column studies.type is 'Тип исследования';
comment on column studies.patient is 'Идентификатор пациента'
