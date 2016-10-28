create table if not exists patients
(
	id serial primary key,
	fio character varying not null,
	date_of_birth date not null,
	sex boolean,
	weight int,
	unique (fio, date_of_birth)
);

comment on column patients.id is 'Идентификатор пациента';
comment on column patients.fio is 'Фамилмия Имя Отчество';
comment on column patients.date_of_birth is 'Дата рождения';
comment on column patients.sex is 'Пол (true - мужской, false - женский)';
comment on column patients.weight is 'Вес';

create table if not exists studies
(
	patient int references patients (id) match simple on update cascade on delete cascade,
	type character varying not null,
	date date
);
create index on studies (patient);

comment on column studies.date is 'Дата исследования';
comment on column studies.type is 'Тип исследования';
comment on column studies.patient is 'Идентификатор пациента'
